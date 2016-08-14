--TEST--
AlpmHandle ignorepkg remove test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_ignorepkg("bash");

if ($h->remove_ignorepkg("bash")) {
    echo "removed ignorepkg";
}
?>
--EXPECT--
removed ignorepkg
