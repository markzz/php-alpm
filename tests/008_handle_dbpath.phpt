--TEST--
AlpmHandle dbpath test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

echo $h->dbpath === $pwd . "/test_root/var/lib/pacman/" ? "pass" : "fail";
?>
--EXPECT--
pass