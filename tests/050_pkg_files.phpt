--TEST--
AlpmPkg builddate test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$pkg = $h->load_pkg($pwd . "/testpkg-0.1-1-any.pkg.tar.xz");
var_dump($pkg->get_files());
?>
--EXPECT--
array(3) {
  [0]=>
  array(3) {
    [0]=>
    string(4) "etc/"
    [1]=>
    int(0)
    [2]=>
    int(16877)
  }
  [1]=>
  array(3) {
    [0]=>
    string(8) "etc/test"
    [1]=>
    int(10)
    [2]=>
    int(33188)
  }
  [2]=>
  array(3) {
    [0]=>
    string(4) "test"
    [1]=>
    int(10)
    [2]=>
    int(33188)
  }
}

