--TEST--
AlpmHandle cachedirs get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_cachedir($pwd . "/test_root/var/cache/pacman/pkg");
$h->add_cachedir($pwd . "/test_root/var/cache/pacman/pkg2");

$cachedirs = $h->get_cachedirs();
if ($cachedirs[0] === $pwd . "/test_root/var/cache/pacman/pkg/" && $cachedirs[1] === $pwd . "/test_root/var/cache/pacman/pkg2/") {
    echo "got cachedirs";
}
?>
--EXPECT--
got cachedirs
