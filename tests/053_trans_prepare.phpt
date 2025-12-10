--TEST--
AlpmTransaction prepare test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

// Load a package
$pkg = $h->load_pkg($pwd . "/tests/testpkg/testpkg-1.0.0-1-any.pkg.tar.zst");

// Create transaction with nodeps=true (first parameter)
$trans = $h->init_transaction(true);

// Add package
$trans->add_pkg($pkg);

// Prepare the transaction - returns null on success or array with errors
$result = $trans->prepare();
echo $result === null ? "prepared ok" : "prepare returned data";

$trans->release();
?>
--EXPECT--
prepared ok
