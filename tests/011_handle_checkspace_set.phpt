--TEST--
AlpmHandle checkspace set test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->set_checkspace(1)) {
    echo "set checkspace";
}
?>
--EXPECT--
set checkspace
