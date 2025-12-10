--TEST--
AlpmHandle noupgrades test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_noupgrade("/var/cache/pacman")) {
    echo "added noupgrade";
}

if ($h->add_noupgrade("/noupgrade2")) {
    echo "added noupgrade";
}

echo $h->noupgrades[0];
echo $h->noupgrades[1];

$h->remove_noupgrade("/var/cache/pacman");

echo $h->noupgrades[0];

$h->remove_noupgrade("/noupgrade2");

echo $h->noupgrades == null ? 1 : 0;
?>
--EXPECT--
added noupgradeadded noupgrade/var/cache/pacman/noupgrade2/noupgrade21

