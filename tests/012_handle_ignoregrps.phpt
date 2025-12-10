--TEST--
AlpmHandle ignoregrps test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

if ($h->add_ignoregrp("gnome")) {
    echo "added ignoregrp";
}

if ($h->add_ignoregrp("base")) {
    echo "added ignoregrp";
}

echo $h->ignoregrps[0];
echo $h->ignoregrps[1];

$h->remove_ignoregrp("gnome");

echo $h->ignoregrps[0];

$h->remove_ignoregrp("base");

echo $h->ignoregrps == null ? 1 : 0;
?>
--EXPECT--
added ignoregrpadded ignoregrpgnomebasebase1

