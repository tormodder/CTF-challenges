<?php
$file = $_GET['file'];

if (isset($file)) {

    if (strpos($file, '../') !== false) {
      $file = str_replace('../', '', $file);
    }

    if (preg_match('/^\/flag\.txt$/', $file)) {
      $file = '';
    }

    if (file_exists($file)) {
      include($file);
    } else {
      header("Location: /?file=index.html");
      exit;
    }
} else {
    header("Location: /?file=index.html");
    exit;
}
?>

