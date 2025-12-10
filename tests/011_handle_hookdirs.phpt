--TEST--
AlpmHandle hookdirs test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_hookdir("/var/cache/pacman")) {
    echo "added hookdir";
}

if ($h->add_hookdir("/hookdir2")) {
    echo "added hookdir";
}

echo $h->hookdirs[1];
echo $h->hookdirs[2];

$h->remove_hookdir("/var/cache/pacman");

echo $h->hookdirs[1];

$h->remove_hookdir("/hookdir2");

echo $h->hookdirs == null ? 1 : 0;
?>
--EXPECT--
added hookdiradded hookdir/var/cache/pacman//hookdir2//hookdir2/0

