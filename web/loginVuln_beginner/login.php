<?php
session_start();
header('Content-Type: application/json');

$servername = "db"; // Docker service name for the database
$username = "root";
$password = "rootpassword";
$dbname = "vuln_db";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die(json_encode(["Error" => $conn->connect_error]));
}

$user = $_POST['username'];
$pass = $_POST['password'];

$sql = "SELECT * FROM users WHERE username = '$user' AND password = '$pass'";
$result = $conn->query($sql);


if ($result->num_rows > 0) {
    $_SESSION['user'] = $user; // Set a session variable for the user
    echo json_encode(['success' => true]);
    exit();
} else {
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        header('Content-Type: application/json');
        echo json_encode(['success' => false, 'sql' => $sql]);
        exit();
    }
}

$conn->close();

