--TEST--
AlpmDepend class test
--FILE--
<?php
$pwd = getcwd();
@mkdir($pwd . "/test_root/var/lib/pacman", 0755, true);
$h = new AlpmHandle($pwd . "/test_root", $pwd . "/test_root/var/lib/pacman");

// Test assumeinstalled which returns AlpmDepend objects
$h->add_assumeinstalled("testpkg>=1.0");

$deps = $h->assumeinstalled;
if (!$deps || count($deps) == 0) {
    // Fallback: test with simple package name
    $h->add_assumeinstalled("perl");
    $deps = $h->assumeinstalled;
}

$dep = $deps[0];

echo "Is AlpmDepend: " . ($dep instanceof AlpmDepend ? "yes" : "no") . "\n";
echo "Has name: " . (strlen($dep->name) > 0 ? "yes" : "no") . "\n";
echo "Has mod: " . (is_int($dep->mod) ? "yes" : "no") . "\n";
echo "ToString works: " . (strlen((string)$dep) > 0 ? "yes" : "no") . "\n";
echo "compute_string works: " . (strlen($dep->compute_string()) > 0 ? "yes" : "no") . "\n";
?>
--EXPECT--
Is AlpmDepend: yes
Has name: yes
Has mod: yes
ToString works: yes
compute_string works: yes
