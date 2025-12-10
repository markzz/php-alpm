--TEST--
AlpmGroup class test
--FILE--
<?php
$pwd = getcwd();
@mkdir($pwd . "/test_root/var/lib/pacman", 0755, true);
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$db = $h->register_syncdb("testdb", ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL);

$grpcache = $db->grpcache;
if ($grpcache && count($grpcache) > 0) {
    $group = $grpcache[0];
    echo "Is AlpmGroup: " . ($group instanceof AlpmGroup ? "yes" : "no") . "\n";
    echo "Has name: " . (strlen($group->name) > 0 ? "yes" : "no") . "\n";
    echo "Name: " . $group->name . "\n";
    echo "ToString: " . (string)$group . "\n";
    echo "Has packages: " . (is_array($group->packages) ? "yes" : "no") . "\n";
} else {
    echo "No groups found\n";
}
?>
--EXPECT--
Is AlpmGroup: yes
Has name: yes
Name: special-group
ToString: special-group
Has packages: yes
