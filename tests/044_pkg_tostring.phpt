--TEST--
AlpmPkg __toString test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$pkg = $h->load_pkg($pwd . "/tests/testpkg/testpkg-1.0.0-1-any.pkg.tar.zst");
$str = (string)$pkg;
echo is_string($str) ? "is string" : "not string";
echo "\n";
echo $str;
?>
--EXPECT--
is string
testpkg 1.0.0-1
