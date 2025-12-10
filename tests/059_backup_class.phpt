--TEST--
AlpmBackup class test
--FILE--
<?php
$pwd = getcwd();
@mkdir($pwd . "/test_root/var/lib/pacman", 0755, true);
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

// Load a package and check its backup files
$pkg = $h->load_pkg($pwd . "/tests/testpkg/testpkg-1.0.0-1-any.pkg.tar.zst");

$backup = $pkg->backup;
if ($backup && count($backup) > 0) {
    $bkp = $backup[0];
    echo "Is AlpmBackup: " . ($bkp instanceof AlpmBackup ? "yes" : "no") . "\n";
    echo "Has name: " . (strlen($bkp->name) > 0 ? "yes" : "no") . "\n";
    echo "ToString works: " . (strlen((string)$bkp) > 0 ? "yes" : "no") . "\n";
} else {
    echo "No backup files (expected for test package)\n";
    echo "AlpmBackup class exists: " . (class_exists('AlpmBackup') ? "yes" : "no") . "\n";
}
?>
--EXPECT--
No backup files (expected for test package)
AlpmBackup class exists: yes
