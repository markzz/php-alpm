--TEST--
AlpmHandle ignorepkgs test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_ignorepkg("linux")) {
    echo "added ignorepkg";
}

if ($h->add_ignorepkg("xz")) {
    echo "added ignorepkg";
}

echo $h->ignorepkgs[0];
echo $h->ignorepkgs[1];

$h->remove_ignorepkg("linux");

echo $h->ignorepkgs[0];

$h->remove_ignorepkg("xz");

echo $h->ignorepkgs == null ? 1 : 0;
?>
--EXPECT--
added ignorepkgadded ignorepkglinuxxzxz1

