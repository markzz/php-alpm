--TEST--
AlpmHandle noextracts test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_noextract("/var/cache/pacman")) {
    echo "added noextract";
}

if ($h->add_noextract("/noextract2")) {
    echo "added noextract";
}

echo $h->noextracts[0];
echo $h->noextracts[1];

$h->remove_noextract("/var/cache/pacman");

echo $h->noextracts[0];

$h->remove_noextract("/noextract2");

echo $h->noextracts == null ? 1 : 0;
?>
--EXPECT--
added noextractadded noextract/var/cache/pacman/noextract2/noextract21

