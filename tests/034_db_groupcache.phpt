--TEST--
AlpmDb groupcache get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$db = $h->register_syncdb("core", ALPM_SIG_USE_DEFAULT);

$grpcache = $db->get_grpcache();
foreach ($grpcache as $grp) {
    echo $grp;
}
?>
--EXPECT--
base-develbase
