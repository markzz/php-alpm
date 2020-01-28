--TEST--
AlpmHandle local file siglevel test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->default_siglevel = ALPM_SIG_USE_DEFAULT; /* to get a non-zero on the next call */
$h->local_file_siglevel = ALPM_SIG_USE_DEFAULT;
echo $h->local_file_siglevel;
$h->local_file_siglevel = ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL;
echo $h->local_file_siglevel;
?>
--EXPECT--
02049