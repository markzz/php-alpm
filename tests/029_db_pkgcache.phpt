--TEST--
AlpmDb pkgcache test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$db = $h->register_syncdb("testdb", ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL);

var_dump($db->pkgcache);
?>
--EXPECT--
array(1) {
  [0]=>
  string(7) "testpkg"
}