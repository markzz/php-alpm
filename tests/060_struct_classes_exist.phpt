--TEST--
All struct classes exist test
--FILE--
<?php
// Test that all new struct classes are registered
$classes = [
    'AlpmDepend',
    'AlpmFile',
    'AlpmBackup',
    'AlpmGroup',
    'AlpmConflict',
    'AlpmDepMissing',
    'AlpmFileConflict',
];

foreach ($classes as $class) {
    echo "$class exists: " . (class_exists($class) ? "yes" : "no") . "\n";
}

// Test that file conflict constants exist
echo "ALPM_FILECONFLICT_TARGET: " . (defined('ALPM_FILECONFLICT_TARGET') ? "yes" : "no") . "\n";
echo "ALPM_FILECONFLICT_FILESYSTEM: " . (defined('ALPM_FILECONFLICT_FILESYSTEM') ? "yes" : "no") . "\n";
?>
--EXPECT--
AlpmDepend exists: yes
AlpmFile exists: yes
AlpmBackup exists: yes
AlpmGroup exists: yes
AlpmConflict exists: yes
AlpmDepMissing exists: yes
AlpmFileConflict exists: yes
ALPM_FILECONFLICT_TARGET: yes
ALPM_FILECONFLICT_FILESYSTEM: yes
