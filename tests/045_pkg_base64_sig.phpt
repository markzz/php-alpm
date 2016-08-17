--TEST--
AlpmPkg base64 signature get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$db = $h->register_syncdb("core", ALPM_SIG_USE_DEFAULT);
$pkg = $db->get_pkg("linux");
echo strlen($pkg->get_base64_sig());
?>
--EXPECT--
384
