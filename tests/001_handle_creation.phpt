--TEST--
AlpmHandle::__construct() - basic test of creating AlpmHandle object
--FILE--
<?php
/* This bit is to create the required directories for creating a handle.
 * Basically, we're creating a very basic Arch Linux system in the current directory
 */
$pwd = getcwd();
@mkdir($pwd . "/test_root/", 0755, true);
@mkdir($pwd . "/test_root/var/cache/pacman/pkg", 0755, true);
@mkdir($pwd . "/test_root/var/lib/pacman", 0755, true);
@mkdir($pwd . "/test_root/var/log", 0755, true);
@mkdir($pwd . "/test_root/tmp", 1777, true);
@mkdir($pwd . "/test_root/sys", 0555, true);
@mkdir($pwd . "/test_root/proc", 0555, true);

/* set up handle */
if ($h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman")) {
    echo "AlpmHandle created with no error";
}
?>
--EXPECT--
AlpmHandle created with no error
