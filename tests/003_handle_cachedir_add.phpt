--TEST--
AlpmHandle cachedir add test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_cachedir($pwd . "/test_root/var/cache/pacman/pkg")) {
    echo "added cachedir";
}
?>
--EXPECT--
added cachedir
