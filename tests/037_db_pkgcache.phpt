--TEST--
AlpmDb pkgcache test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$db = $h->register_syncdb("core", ALPM_SIG_USE_DEFAULT);
echo count($db->get_pkgcache());
?>
--EXPECT--
212
