--TEST--
AlpmHandle arch test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_architecture("i686");
echo $h->architectures[0];
$h->add_architecture("x86_64");
echo $h->architectures[1];
$h->remove_architecture("i686");
echo $h->architectures[0];
?>
--EXPECT--
i686x86_64x86_64
