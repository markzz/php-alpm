--TEST--
AlpmTransaction add_pkg test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

// Load a package
$pkg = $h->load_pkg($pwd . "/tests/testpkg/testpkg-1.0.0-1-any.pkg.tar.zst");

// Create transaction
$trans = $h->init_transaction();

// Add package to transaction
$result = $trans->add_pkg($pkg);
echo $result ? "added" : "not added";
echo "\n";

// Check get_add now has the package
$add = $trans->get_add();
echo count($add);
echo "\n";
echo $add[0] instanceof AlpmPkg ? "is AlpmPkg" : "not AlpmPkg";

$trans->release();
?>
--EXPECT--
added
1
is AlpmPkg
