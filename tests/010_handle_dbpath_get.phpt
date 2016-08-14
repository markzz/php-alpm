--TEST--
AlpmHandle dbpath get test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
if ($h->get_dbpath() === $pwd . "/test_root/var/lib/pacman/") {
    echo "got dbpath";
}
?>
--EXPECT--
got dbpath
