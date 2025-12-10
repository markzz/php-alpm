--TEST--
AlpmDb search test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$localdb = $h->get_localdb();

// Search on empty local db returns empty array
$results = $localdb->search(["test"]);
echo is_array($results) ? "is array" : "not array";
echo "\n";
echo count($results);
?>
--EXPECT--
is array
0
