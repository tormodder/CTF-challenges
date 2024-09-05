<?php
$file = $_GET['file'];

if (isset($file)) {
    include($file);
} else {
    header("Location: /?file=index.html");
    exit;
}
?>

