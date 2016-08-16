--TEST--
AlpmDb pkg get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$db = $h->register_syncdb("core", ALPM_SIG_USE_DEFAULT);
$pkg = $db->get_pkg("xz");
echo $pkg->get_name();
?>
--EXPECT--
xz
