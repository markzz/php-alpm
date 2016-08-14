--TEST--
AlpmHandle arch get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$h->set_arch("i686");
echo $h->get_arch();
?>
--EXPECT--
i686
