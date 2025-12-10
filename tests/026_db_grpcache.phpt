--TEST--
AlpmDb grpcache test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$db = $h->register_syncdb("testdb", ALPM_SIG_PACKAGE|ALPM_SIG_DATABASE_OPTIONAL);

$grpcache = $db->grpcache;
var_dump($grpcache);
?>
--EXPECT--
array(1) {
  [0]=>
  string(13) "special-group"
}