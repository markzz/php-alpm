--TEST--
AlpmPkg replaces test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$pkg = $h->load_pkg($pwd . "/testpkg-0.1-1-any.pkg.tar.xz");
echo $pkg->get_replaces()[0];
?>
--EXPECT--
testingpkg