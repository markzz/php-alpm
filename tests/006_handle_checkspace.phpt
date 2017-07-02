--TEST--
AlpmHandle checkspace test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->checkspace = false;
echo $h->checkspace ? 1 : 0;
$h->checkspace = true;
echo $h->checkspace ? 1 : 0;
?>
--EXPECT--
01