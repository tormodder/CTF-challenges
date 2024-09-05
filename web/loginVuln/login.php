<?php
$servername = "db"; // Docker service name for the database
$username = "root";
$password = "rootpassword";
$dbname = "vuln_db";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$user = $_POST['username'];
$pass = $_POST['password'];

$sql = "SELECT * FROM users WHERE username = '$user' AND password = '$pass'";
$result = $conn->query($sql);

// DEBUG
//echo "Debug SQL query: " . $sql . "<br>";

if ($result->num_rows > 0) {
    echo "CTFkom{awnaw_my_login_page_is_really_vulnerable}";
    exit();
} else {
    echo "Login failed";
}

$conn->close();
?>
