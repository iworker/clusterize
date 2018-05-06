--TEST--
Simple Cluster: [ [ 10, 10 ], [ 12, 12 ], [ 30, 30 ], [ 32, 32 ] ] -> [ [ 11, 11 ], [ 31, 31 ] ]
--FILE--
<?php

$points = [ [ 10, 10], [ 12, 12 ], [ 30, 30 ], [ 32, 32 ] ];
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
    float(11)
    [1]=>
    float(11)
    [2]=>
    float(2)
  }
  [1]=>
  array(3) {
    [0]=>
    float(31)
    [1]=>
    float(31)
    [2]=>
    float(2)
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
  int(1)
}
