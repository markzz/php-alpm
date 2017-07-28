--TEST--
AlpmDb usage test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$db = $h->register_syncdb("testdb", ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL);

$db->usage = ALPM_DB_USAGE_INSTALL;
echo $db->usage;
$db->usage = ALPM_DB_USAGE_ALL;
echo $db->usage;
?>
--EXPECT--
415