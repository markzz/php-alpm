--TEST--
AlpmPkg has_scriptlet test
--FILE--
<?php
$pwd = getcwd();
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

$pkg = $h->load_pkg($pwd . "/tests/testpkg/testpkg-1.0.0-1-any.pkg.tar.zst");

// Our test package has no scriptlet
echo $pkg->has_scriptlet ? "has scriptlet" : "no scriptlet";
?>
--EXPECT--
no scriptlet
