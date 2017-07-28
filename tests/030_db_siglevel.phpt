--TEST--
AlpmDb siglevel test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$db = $h->register_syncdb("testdb", ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL);

echo $db->siglevel === ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL ? "pass" : "fail";
?>
--EXPECT--
pass