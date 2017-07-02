--TEST--
AlpmHandle remote file siglevel test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->default_siglevel = ALPM_SIG_USE_DEFAULT; /* to get a non-zero on the next call */
$h->remote_file_siglevel = ALPM_SIG_USE_DEFAULT;
echo $h->remote_file_siglevel;
$h->remote_file_siglevel = ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL;
echo $h->remote_file_siglevel;
?>
--EXPECT--
10737418242049