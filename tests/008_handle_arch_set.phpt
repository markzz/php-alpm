--TEST--
AlpmHandle arch set test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->set_arch("i686")) {
    echo "set arch";
}
?>
--EXPECT--
set arch
