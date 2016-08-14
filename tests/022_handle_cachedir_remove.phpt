--TEST--
AlpmHandle cachedir remove test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_cachedir($pwd . "/test_root/var/cache/pacman/pkg");

if ($h->remove_cachedir($pwd . "/test_root/var/cache/pacman/pkg")) {
    echo "removed cachedir";
}
?>
--EXPECT--
removed cachedir
