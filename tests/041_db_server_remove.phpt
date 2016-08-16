--TEST--
AlpmDb server remove test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$db = $h->register_syncdb("core", ALPM_SIG_USE_DEFAULT);
$db->add_server("http://mirrors.kernel.org/archlinux/core/os/i686");

if ($db->remove_server("http://mirrors.kernel.org/archlinux/core/os/i686")) {
    echo "removed server";
}
?>
--EXPECT--
removed server
