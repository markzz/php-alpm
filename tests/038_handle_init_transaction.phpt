--TEST--
AlpmHandle init_transaction test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$trans = $h->init_transaction();
echo $trans instanceof AlpmTransaction ? "is AlpmTransaction" : "not AlpmTransaction";
echo "\n";

// Release the transaction
$trans->release();
echo "released";
?>
--EXPECT--
is AlpmTransaction
released
