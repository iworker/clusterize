--TEST--
Any points and require_once specific file
--FILE--
<?php

$result = clusterize([[1,1]], 1);

var_dump($result);

require_once("test.php");
?>
--EXPECT--
array(2) {
  [0]=>
  array(1) {
    [0]=>
    array(3) {
      [0]=>
      float(1)
      [1]=>
      float(1)
      [2]=>
      float(1)
    }
  }
  [1]=>
  array(1) {
    [0]=>
    int(0)
  }
}
