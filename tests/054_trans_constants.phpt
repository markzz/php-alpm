--TEST--
AlpmTransaction flag constants test
--FILE--
<?php
// Check all transaction flag constants are defined
$constants = [
    'ALPM_TRANS_FLAG_NODEPS',
    'ALPM_TRANS_FLAG_NOSAVE',
    'ALPM_TRANS_FLAG_NODEPVERSION',
    'ALPM_TRANS_FLAG_CASCADE',
    'ALPM_TRANS_FLAG_RECURSE',
    'ALPM_TRANS_FLAG_DBONLY',
    'ALPM_TRANS_FLAG_ALLDEPS',
    'ALPM_TRANS_FLAG_DOWNLOADONLY',
    'ALPM_TRANS_FLAG_NOSCRIPTLET',
    'ALPM_TRANS_FLAG_NOCONFLICTS',
    'ALPM_TRANS_FLAG_NEEDED',
    'ALPM_TRANS_FLAG_ALLEXPLICIT',
    'ALPM_TRANS_FLAG_UNNEEDED',
    'ALPM_TRANS_FLAG_RECURSEALL',
    'ALPM_TRANS_FLAG_NOLOCK',
];

$all_defined = true;
foreach ($constants as $const) {
    if (!defined($const)) {
        echo "Missing: $const\n";
        $all_defined = false;
    }
}

if ($all_defined) {
    echo "All constants defined\n";
}

// Check they're all integers
$all_ints = true;
foreach ($constants as $const) {
    if (!is_int(constant($const))) {
        $all_ints = false;
    }
}
echo $all_ints ? "All are integers" : "Some are not integers";
?>
--EXPECT--
All constants defined
All are integers
