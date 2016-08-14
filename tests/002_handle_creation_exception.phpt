--TEST--
AlpmHandle creation exception test
--FILE--
<?php
try {
    $h = new AlpmHandle("adfjs", "daljfh");
} catch (AlpmHandleException $e) {
    echo "caught exception";
}
?>
--EXPECT--
caught exception
