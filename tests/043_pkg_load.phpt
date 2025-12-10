--TEST--
AlpmHandle load_pkg test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$pkg = $h->load_pkg($pwd . "/tests/testpkg/testpkg-1.0.0-1-any.pkg.tar.zst");
echo $pkg instanceof AlpmPkg ? "is AlpmPkg" : "not AlpmPkg";
echo "\n";
echo $pkg->name;
echo "\n";
echo $pkg->version;
?>
--EXPECT--
is AlpmPkg
testpkg
1.0.0-1
