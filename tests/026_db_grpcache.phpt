--TEST--
AlpmDb grpcache test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$db = $h->register_syncdb("testdb", ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL);

$grpcache = $db->grpcache;
if (is_array($grpcache) && count($grpcache) > 0) {
    echo "Got grpcache array\n";
    echo "First group name: " . $grpcache[0]->name . "\n";
    echo "Is AlpmGroup: " . ($grpcache[0] instanceof AlpmGroup ? "yes" : "no") . "\n";
} else {
    echo "No groups found\n";
}
?>
--EXPECT--
Got grpcache array
First group name: special-group
Is AlpmGroup: yes