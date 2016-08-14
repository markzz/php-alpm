--TEST--
AlpmHandle cachedir remove failure test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if (!$h->remove_cachedir($pwd . "/test_root/var/cache/pacman/pkg")) {
    echo "did not remove cachedir";
}
?>
--EXPECT--
did not remove cachedir
