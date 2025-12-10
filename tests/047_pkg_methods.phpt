--TEST--
AlpmPkg methods test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$pkg = $h->load_pkg($pwd . "/tests/testpkg/testpkg-1.0.0-1-any.pkg.tar.zst");

// compute_requiredby - should return empty array for uninstalled package
$requiredby = $pkg->compute_requiredby();
echo is_array($requiredby) ? "is array" : "not array";
echo "\n";

// get_xdata - returns extended data (may be null for simple packages)
$xdata = $pkg->get_xdata();
echo $xdata === null || is_array($xdata) ? "valid xdata" : "invalid xdata";
?>
--EXPECT--
is array
valid xdata
