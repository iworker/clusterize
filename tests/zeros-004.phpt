--TEST--
Zero values cluster: [ [ 5, 5 ], [ 10, 10 ], [ 20, 20 ], [ 0, 0 ]]
--FILE--
<?php

$points = [ [ 5, 5 ], [ 10, 10 ], [ 20, 20 ], [ 0, 0 ] ];
$count_of_clusters = 2;
list ($clusters, $points_by_clusters) = clusterize($points, $count_of_clusters);

var_dump($clusters);
var_dump($points_by_clusters);
?>
--EXPECT--
array(2) {
  [0]=>
  array(3) {
    [0]=>
    float(5)
    [1]=>
    float(5)
    [2]=>
    float(3)
  }
  [1]=>
  array(3) {
    [0]=>
    float(20)
    [1]=>
    float(20)
    [2]=>
    float(1)
  }
}
array(4) {
  [0]=>
  int(0)
  [1]=>
  int(0)
  [2]=>
  int(1)
  [3]=>
  int(0)
}
