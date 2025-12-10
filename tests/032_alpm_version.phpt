--TEST--
alpm_version() function test
--FILE--
<?php
$ver = alpm_version();
echo is_string($ver) ? "string" : "not string";
echo "\n";
// Version should match pattern like "14.0.0" or similar
echo preg_match('/^\d+\.\d+\.\d+/', $ver) ? "valid format" : "invalid format";
?>
--EXPECT--
string
valid format
