--TEST--
alpm_vercmp() function test
--FILE--
<?php
// Equal versions
echo alpm_vercmp("1.0.0", "1.0.0") === 0 ? "equal" : "not equal";
echo "\n";

// First version greater
echo alpm_vercmp("2.0.0", "1.0.0") > 0 ? "greater" : "not greater";
echo "\n";

// First version less
echo alpm_vercmp("1.0.0", "2.0.0") < 0 ? "less" : "not less";
echo "\n";

// Compare with epoch
echo alpm_vercmp("1:1.0.0", "2.0.0") > 0 ? "epoch wins" : "epoch loses";
echo "\n";

// Compare with release
echo alpm_vercmp("1.0.0-2", "1.0.0-1") > 0 ? "rel2 > rel1" : "rel2 <= rel1";
?>
--EXPECT--
equal
greater
less
epoch wins
rel2 > rel1
