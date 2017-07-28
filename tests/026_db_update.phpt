--TEST--
AlpmDb update test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$db = $h->register_syncdb("testdb", ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL);

if ($db->add_server("file://" . $pwd . "/testdb")) {
    echo "added server";
}

if ($db->update(1)) {
    echo "updated";
}
?>
--EXPECT--
added serverupdated