--TEST--
AlpmHandle ignoregrp add test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_ignoregrp("kde")) {
    echo "added ignoregrp";
}
?>
--EXPECT--
added ignoregrp
