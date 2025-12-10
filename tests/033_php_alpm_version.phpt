--TEST--
php_alpm_version() function test
--FILE--
<?php
$ver = php_alpm_version();
echo is_string($ver) ? "string" : "not string";
echo "\n";
// Version should match pattern like "0.8" or similar
echo preg_match('/^\d+\.\d+/', $ver) ? "valid format" : "invalid format";
?>
--EXPECT--
string
valid format
