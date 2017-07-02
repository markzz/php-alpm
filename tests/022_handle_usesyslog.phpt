--TEST--
AlpmHandle lockfile test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->usesyslog = false;
echo $h->usesyslog ? 1 : 0;
$h->usesyslog = true;
echo $h->usesyslog ? 1 : 0;
?>
--EXPECT--
01