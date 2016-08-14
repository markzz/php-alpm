--TEST--
AlpmHandle ignoregrp remove failure test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if (!$h->remove_ignoregrp("base")) {
    echo "did not remove ignoregrp";
}
?>
--EXPECT--
did not remove ignoregrp
