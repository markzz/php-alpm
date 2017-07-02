--TEST--
AlpmHandle root test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

echo $h->root === $pwd . "/test_root/" ? 1 : 0;
?>
--EXPECT--
1