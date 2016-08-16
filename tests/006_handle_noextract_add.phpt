--TEST--
AlpmHandle noextract add test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_noextract($pwd . "/test_root/etc/testfile")) {
    echo "added noextract";
}
?>
--EXPECT--
added noextract