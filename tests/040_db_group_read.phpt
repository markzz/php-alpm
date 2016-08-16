--TEST--
AlpmDb group read test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$db = $h->register_syncdb("core", ALPM_SIG_USE_DEFAULT);
$bd = $db->read_grp('base-devel')['base-devel'];
echo count($bd);
?>
--EXPECT--
25
