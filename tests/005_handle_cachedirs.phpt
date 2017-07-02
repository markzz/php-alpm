--TEST--
AlpmHandle cachedirs test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_cachedir("/var/cache/pacman")) {
    echo "added cachedir";
}

if ($h->add_cachedir("/cachedir2")) {
    echo "added cachedir";
}

echo $h->cachedirs[0];
echo $h->cachedirs[1];

$h->remove_cachedir("/var/cache/pacman");

echo $h->cachedirs[0];

$h->remove_cachedir("/cachedir2");

echo $h->cachedirs == null ? 1 : 0;
?>
--EXPECT--
added cachediradded cachedir/var/cache/pacman//cachedir2//cachedir2/1

