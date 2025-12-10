--TEST--
AlpmDb get_pkg test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$localdb = $h->get_localdb();

// Get non-existent package returns null
$pkg = $localdb->get_pkg("nonexistent-package");
echo $pkg === null ? "null" : "not null";
?>
--EXPECT--
null
