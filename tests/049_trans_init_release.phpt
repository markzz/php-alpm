--TEST--
AlpmTransaction init and release test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

// Create a transaction
$trans = $h->init_transaction();
echo $trans instanceof AlpmTransaction ? "is AlpmTransaction" : "not AlpmTransaction";
echo "\n";

// Release it (returns null on success)
$result = $trans->release();
echo $result === null ? "released" : "not released";
?>
--EXPECT--
is AlpmTransaction
released
