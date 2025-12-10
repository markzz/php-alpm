--TEST--
AlpmDb server test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$db = $h->register_syncdb("testdb", ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL);

if ($db->add_server("file://" . $pwd . "/testdb")) {
    echo "added server";
}

if ($db->add_server("http://repo.example.com/")) {
    echo "added server";
}

echo $db->servers[0];
echo $db->servers[1];

$db->remove_server("file://" . $pwd . "/testdb");

echo $db->servers[0];

$db->remove_server("http://repo.example.com/");

echo $db->servers === null ? 1 : 0;
?>
--EXPECTF--
added serveradded serverfile://%s/testdbhttp://repo.example.comhttp://repo.example.com1