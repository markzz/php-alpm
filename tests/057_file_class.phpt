--TEST--
AlpmFile class test
--FILE--
<?php
$pwd = getcwd();
@mkdir($pwd . "/test_root/var/lib/pacman", 0755, true);
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

// Load a package and check its files
$pkg = $h->load_pkg($pwd . "/tests/testpkg/testpkg-1.0.0-1-any.pkg.tar.zst");

$files = $pkg->files;
if ($files && count($files) > 0) {
    $file = $files[0];
    echo "Is AlpmFile: " . ($file instanceof AlpmFile ? "yes" : "no") . "\n";
    echo "Has name: " . (strlen($file->name) > 0 ? "yes" : "no") . "\n";
    echo "Has size: " . (is_int($file->size) ? "yes" : "no") . "\n";
    echo "Has mode: " . (is_int($file->mode) ? "yes" : "no") . "\n";
    echo "ToString works: " . (strlen((string)$file) > 0 ? "yes" : "no") . "\n";
} else {
    echo "Package has files: no\n";
}
?>
--EXPECT--
Is AlpmFile: yes
Has name: yes
Has size: yes
Has mode: yes
ToString works: yes
