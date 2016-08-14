--TEST--
AlpmHandle noextract remove test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_noextract($pwd . "/test");

if ($h->add_noextract($pwd . "/test")) {
    echo "removed noextract";
}
?>
--EXPECT--
removed noextract
