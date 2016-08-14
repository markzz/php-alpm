--TEST--
AlpmHandle register_syncdb test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$db = $h->register_syncdb("core", ALPM_SIG_USE_DEFAULT);
echo $db->get_name();
?>
--EXPECT--
core
