--TEST--
AlpmHandle get_syncdbs test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

// Initially empty (returns null, not empty array)
$syncdbs = $h->get_syncdbs();
echo $syncdbs === null || (is_array($syncdbs) && count($syncdbs) === 0) ? "initially empty" : "not empty";
echo "\n";

// Register a sync db
$db = $h->register_syncdb("core", 0);
$syncdbs = $h->get_syncdbs();
echo is_array($syncdbs) ? "is array" : "not array";
echo "\n";
echo count($syncdbs);
echo "\n";

// Register another
$db2 = $h->register_syncdb("extra", 0);
$syncdbs = $h->get_syncdbs();
echo count($syncdbs);
echo "\n";

// Check they're AlpmDb instances
echo $syncdbs[0] instanceof AlpmDb ? "first is AlpmDb" : "first not AlpmDb";
?>
--EXPECT--
initially empty
is array
1
2
first is AlpmDb
