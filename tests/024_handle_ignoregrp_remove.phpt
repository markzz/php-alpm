--TEST--
AlpmHandle ignoregrp remove test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$h->add_ignoregrp("base");

if ($h->remove_ignoregrp("base")) {
    echo "removed ignoregrp";
}
?>
--EXPECT--
removed ignoregrp
