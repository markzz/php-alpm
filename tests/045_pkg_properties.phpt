--TEST--
AlpmPkg properties test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$pkg = $h->load_pkg($pwd . "/tests/testpkg/testpkg-1.0.0-1-any.pkg.tar.zst");

// Basic properties
echo "name: " . $pkg->name . "\n";
echo "version: " . $pkg->version . "\n";
echo "desc: " . $pkg->desc . "\n";
echo "url: " . $pkg->url . "\n";
echo "arch: " . $pkg->arch . "\n";
echo "packager: " . $pkg->packager . "\n";

// Builddate should be a timestamp
echo "builddate: " . (is_int($pkg->builddate) ? "is int" : "not int") . "\n";

// Size properties
echo "size: " . (is_int($pkg->size) ? "is int" : "not int") . "\n";
echo "isize: " . (is_int($pkg->isize) ? "is int" : "not int") . "\n";
?>
--EXPECT--
name: testpkg
version: 1.0.0-1
desc: Test package for php-alpm tests
url: https://example.com
arch: any
packager: Test Packager <test@example.com>
builddate: is int
size: is int
isize: is int
