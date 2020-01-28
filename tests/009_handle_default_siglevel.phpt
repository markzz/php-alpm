--TEST--
AlpmHandle default siglevel test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->default_siglevel = ALPM_SIG_USE_DEFAULT;
echo $h->default_siglevel;
$h->default_siglevel = ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL;
echo $h->default_siglevel;
?>
--EXPECT--
02049