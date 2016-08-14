--TEST--
AlpmHandle ignoregrps get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_ignoregrp("base");
$h->add_ignoregrp("base-devel");

$ignoregrps = $h->get_ignoregrps();
if ($ignoregrps[0] === "base" && $ignoregrps[1] === "base-devel") {
    echo "got ignoregrps";
}
?>
--EXPECT--
got ignoregrps
