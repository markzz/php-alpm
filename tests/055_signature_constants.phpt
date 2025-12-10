--TEST--
Signature constants test
--FILE--
<?php
// Check signature level constants
$sig_constants = [
    'ALPM_SIG_PACKAGE',
    'ALPM_SIG_PACKAGE_OPTIONAL',
    'ALPM_SIG_PACKAGE_MARGINAL_OK',
    'ALPM_SIG_PACKAGE_UNKNOWN_OK',
    'ALPM_SIG_DATABASE',
    'ALPM_SIG_DATABASE_OPTIONAL',
    'ALPM_SIG_DATABASE_MARGINAL_OK',
    'ALPM_SIG_DATABASE_UNKNOWN_OK',
    'ALPM_SIG_USE_DEFAULT',
];

$all_defined = true;
foreach ($sig_constants as $const) {
    if (!defined($const)) {
        echo "Missing: $const\n";
        $all_defined = false;
    }
}

if ($all_defined) {
    echo "All signature constants defined\n";
}

// Check signature status constants
$status_constants = [
    'ALPM_SIGSTATUS_VALID',
    'ALPM_SIGSTATUS_KEY_EXPIRED',
    'ALPM_SIGSTATUS_SIG_EXPIRED',
    'ALPM_SIGSTATUS_KEY_UNKNOWN',
    'ALPM_SIGSTATUS_KEY_DISABLED',
    'ALPM_SIGSTATUS_INVALID',
];

$status_all_defined = true;
foreach ($status_constants as $const) {
    if (!defined($const)) {
        echo "Missing: $const\n";
        $status_all_defined = false;
    }
}

if ($status_all_defined) {
    echo "All status constants defined\n";
}

// Check validity constants
$validity_constants = [
    'ALPM_SIGVALIDITY_FULL',
    'ALPM_SIGVALIDITY_MARGINAL',
    'ALPM_SIGVALIDITY_NEVER',
    'ALPM_SIGVALIDITY_UNKNOWN',
];

$validity_all_defined = true;
foreach ($validity_constants as $const) {
    if (!defined($const)) {
        echo "Missing: $const\n";
        $validity_all_defined = false;
    }
}

if ($validity_all_defined) {
    echo "All validity constants defined";
}
?>
--EXPECT--
All signature constants defined
All status constants defined
All validity constants defined
