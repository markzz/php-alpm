--TEST--
AlpmHandle __toString test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$str = (string)$h;
echo is_string($str) ? "is string" : "not string";
echo "\n";
// Should contain the root path
echo strpos($str, "test_root") !== false ? "contains root" : "missing root";
?>
--EXPECT--
is string
contains root
