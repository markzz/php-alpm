--TEST--
AlpmPkg array properties test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$pkg = $h->load_pkg($pwd . "/tests/testpkg/testpkg-1.0.0-1-any.pkg.tar.zst");

// Licenses
echo "licenses: " . (is_array($pkg->licenses) ? "is array" : "not array") . "\n";
echo "license count: " . count($pkg->licenses) . "\n";

// Depends
echo "depends: " . (is_array($pkg->depends) ? "is array" : "not array") . "\n";

// Provides
echo "provides: " . (is_array($pkg->provides) ? "is array" : "not array") . "\n";

// Files
echo "files: " . (is_array($pkg->files) ? "is array" : "not array") . "\n";
?>
--EXPECT--
licenses: is array
license count: 1
depends: is array
provides: is array
files: is array
