--TEST--
AlpmHandle noextract remove fail test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if (!$h->remove_noextract($pwd . "/test")) {
    echo "did not remove noextract";
}
?>
--EXPECT--
did not remove noextract
