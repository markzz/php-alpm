--TEST--
AlpmHandle get_localdb test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$localdb = $h->get_localdb();
echo $localdb instanceof AlpmDb ? "is AlpmDb" : "not AlpmDb";
echo "\n";
echo $localdb->name;
?>
--EXPECT--
is AlpmDb
local
