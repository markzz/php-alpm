--TEST--
AlpmDb server remove fail test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");
$db = $h->register_syncdb("core", ALPM_SIG_USE_DEFAULT);

if (!$db->remove_server("http://mirrors.kernel.org/archlinux/core/os/i686")) {
    echo "did not remove server";
}
?>
--EXPECT--
did not remove server
