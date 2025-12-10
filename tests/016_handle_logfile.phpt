--TEST--
AlpmHandle logfile test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->logfile = "/path/to/some/log.txt";
echo $h->logfile;
$h->logfile = "/another/log.txt";
echo $h->logfile;
?>
--EXPECT--
/path/to/some/log.txt/another/log.txt