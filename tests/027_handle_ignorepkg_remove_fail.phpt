--TEST--
AlpmHandle ignorepkg remove failure test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if (!$h->remove_ignorepkg("base")) {
    echo "did not remove ignorepkg";
}
?>
--EXPECT--
did not remove ignorepkg
