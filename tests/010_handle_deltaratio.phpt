--TEST--
AlpmHandle deltaratio test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->deltaratio = 0.0;
echo $h->deltaratio;
$h->deltaratio = 0.345;
echo $h->deltaratio;
$h->deltaratio = 1;
echo $h->deltaratio;
?>
--EXPECT--
00.3451