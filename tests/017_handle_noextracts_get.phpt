--TEST--
AlpmHandle ignoregrps get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_noextract("/etc/anything");
$h->add_noextract("/etc/something");

$noextracts = $h->get_noextracts();
if ($noextracts[0] === "/etc/anything" && $noextracts[1] === "/etc/something") {
    echo "got noextracts";
}
?>
--EXPECT--
got noextracts
