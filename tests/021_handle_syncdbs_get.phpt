--TEST--
AlpmHandle syncdbs get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->register_syncdb("core", ALPM_SIG_USE_DEFAULT);
$h->register_syncdb("extra", ALPM_SIG_USE_DEFAULT);

$syncdbs = $h->get_syncdbs();
foreach ($syncdbs as $db) {
    echo $db;
}
?>
--EXPECT--
coreextra
