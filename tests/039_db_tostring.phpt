--TEST--
AlpmDb __toString test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$localdb = $h->get_localdb();
$str = (string)$localdb;
echo is_string($str) ? "is string" : "not string";
echo "\n";
echo $str;
?>
--EXPECT--
is string
local
