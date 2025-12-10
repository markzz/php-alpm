--TEST--
AlpmHandle lockfile test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

echo $h->lockfile === $pwd . "/test_root/var/lib/pacman/db.lck" ? 1 : 0;
?>
--EXPECT--
1