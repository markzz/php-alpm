--TEST--
AlpmHandle checkspace get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$h->set_checkspace(1);
echo $h->get_checkspace();
?>
--EXPECT--
1
