--TEST--
AlpmHandle arch test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->arch = "i686";
echo $h->arch;
$h->arch = "x86_64";
echo $h->arch;
?>
--EXPECT--
i686x86_64
