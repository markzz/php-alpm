--TEST--
AlpmHandle noupgrade remove fail test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if (!$h->remove_noupgrade($pwd . "/test")) {
    echo "did not remove noupgrade";
}
?>
--EXPECT--
did not remove noupgrade
