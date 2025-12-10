--TEST--
AlpmDb read_grp test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$localdb = $h->get_localdb();

// Read non-existent group returns null/empty
$grp = $localdb->read_grp("nonexistent");
echo $grp === null ? "null" : "not null";
?>
--EXPECT--
null
