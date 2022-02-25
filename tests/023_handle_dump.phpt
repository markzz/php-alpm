--TEST--
AlpmHandle var dump test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_architecture("i686");
$h->add_cachedir("/var/cache/pacman");
$h->add_cachedir("/var/cache/pacman2");

var_dump($h);
?>
--EXPECTF--
object(AlpmHandle)#1 (26) {
  ["architectures"]=>
  array(1) {
    [0]=>
    string(4) "i686"
  }
  ["assumeinstalled"]=>
  NULL
  ["cachedir"]=>
  array(2) {
    [0]=>
    string(18) "/var/cache/pacman/"
    [1]=>
    string(19) "/var/cache/pacman2/"
  }
  ["checkspace"]=>
  bool(false)
  ["dbext"]=>
  string(3) ".db"
  ["dbpath"]=>
  string(%d) "%s"
  ["default_siglevel"]=>
  int(0)
  ["dlcb"]=>
  NULL
  ["eventcb"]=>
  NULL
  ["fetchcb"]=>
  NULL
  ["gpgdir"]=>
  NULL
  ["hookdirs"]=>
  array(1) {
    [0]=>
    string(%d) "%s"
  }
  ["ignoregrps"]=>
  NULL
  ["ignorepkgs"]=>
  NULL
  ["local_file_siglevel"]=>
  int(0)
  ["lockfile"]=>
  string(%d) "%s"
  ["logcb"]=>
  NULL
  ["logfile"]=>
  NULL
  ["noextracts"]=>
  NULL
  ["noupgrades"]=>
  NULL
  ["progresscb"]=>
  NULL
  ["questioncb"]=>
  NULL
  ["remote_file_siglevel"]=>
  int(0)
  ["root"]=>
  string(%d) "%s"
  ["totaldlcb"]=>
  NULL
  ["usesyslog"]=>
  bool(false)
}
