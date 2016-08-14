--TEST--
AlpmHandle localdb get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$db = $h->get_localdb();
echo $db->get_name();
?>
--EXPECT--
local
