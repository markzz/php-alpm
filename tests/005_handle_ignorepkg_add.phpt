--TEST--
AlpmHandle ignorepkg add test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_ignorepkg("linux")) {
    echo "added ignorepkg";
}
?>
--EXPECT--
added ignorepkg
