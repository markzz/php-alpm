--TEST--
AlpmHandle ignoregrps get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_ignorepkg("bash");
$h->add_ignorepkg("zsh");

$ignorepkgs = $h->get_ignorepkgs();
if ($ignorepkgs[0] === "bash" && $ignorepkgs[1] === "zsh") {
    echo "got ignorepkgs";
}
?>
--EXPECT--
got ignorepkgs
