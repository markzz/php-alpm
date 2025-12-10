--TEST--
AlpmTransaction flags test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

// Create transaction with default flags (0)
$trans = $h->init_transaction();
$flags = $trans->get_flags();
echo is_int($flags) ? "is int" : "not int";
echo "\n";
echo $flags;
echo "\n";
$trans->release();

// Create transaction with nodeps=true (first param)
// Parameters: nodeps, force, nosave, nodepversion, cascade, recurse, dbonly, alldeps, downloadonly
$trans2 = $h->init_transaction(true);
$flags2 = $trans2->get_flags();
echo ($flags2 & ALPM_TRANS_FLAG_NODEPS) ? "nodeps set" : "nodeps not set";
echo "\n";
$trans2->release();

// Create transaction with nodeps=true and downloadonly=true (1st and 9th params)
$trans3 = $h->init_transaction(true, false, false, false, false, false, false, false, true);
$flags3 = $trans3->get_flags();
echo ($flags3 & ALPM_TRANS_FLAG_NODEPS) ? "nodeps set" : "nodeps not set";
echo "\n";
echo ($flags3 & ALPM_TRANS_FLAG_DOWNLOADONLY) ? "downloadonly set" : "downloadonly not set";
$trans3->release();
?>
--EXPECT--
is int
0
nodeps set
nodeps set
downloadonly set
