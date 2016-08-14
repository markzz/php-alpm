--TEST--
AlpmHandle ignoregrps get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_noupgrade("/etc/anything");
$h->add_noupgrade("/etc/something");

$noupgrades = $h->get_noupgrades();
if ($noupgrades[0] === "/etc/anything" && $noupgrades[1] === "/etc/something") {
    echo "got noupgrades";
}
?>
--EXPECT--
got noupgrades
