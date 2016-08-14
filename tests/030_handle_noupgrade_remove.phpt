--TEST--
AlpmHandle noupgrade remove test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_noupgrade($pwd . "/test");

if ($h->remove_noupgrade($pwd . "/test")) {
    echo "removed noupgrade";
}
?>
--EXPECT--
removed noupgrade
