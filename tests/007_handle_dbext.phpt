--TEST--
AlpmHandle dbext test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

echo $h->dbext;
$h->dbext = ".somethingelse";
echo $h->dbext;
?>
--EXPECT--
.db.somethingelse