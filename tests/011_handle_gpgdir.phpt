--TEST--
AlpmHandle gpgdir test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->gpgdir = "/path/to/some/dir";
echo $h->gpgdir;
$h->gpgdir = "/another/path";
echo $h->gpgdir;
?>
--EXPECT--
/path/to/some/dir//another/path/