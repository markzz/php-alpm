--TEST--
AlpmTransaction get_add and get_remove test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$trans = $h->init_transaction();

// Initially empty
$add = $trans->get_add();
$remove = $trans->get_remove();

echo is_array($add) ? "add is array" : "add not array";
echo "\n";
echo count($add);
echo "\n";

echo is_array($remove) ? "remove is array" : "remove not array";
echo "\n";
echo count($remove);

$trans->release();
?>
--EXPECT--
add is array
0
remove is array
0
