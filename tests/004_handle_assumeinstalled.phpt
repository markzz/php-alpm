--TEST--
AlpmHandle assumeinstalled test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_assumeinstalled("perl")) {
    echo "added assumeinstalled";
}

if ($h->add_assumeinstalled("xz=4.0")) {
    echo "added assumeinstalled";
}

echo $h->assumeinstalled[0]['name'];
echo $h->assumeinstalled[1]['name'];
echo $h->assumeinstalled[1]['version'];
echo $h->assumeinstalled[1]['mod'];

$h->remove_assumeinstalled("perl");

echo $h->assumeinstalled[0]['name'];

$h->remove_assumeinstalled("xz");

echo $h->assumeinstalled == null ? 1 : 0;
?>
--EXPECT--
added assumeinstalledadded assumeinstalledperlxz4.02xz1
