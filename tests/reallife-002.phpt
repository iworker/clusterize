--TEST--
Real life example test
--FILE--
<?php

$points = [
  [ 47.57675, -122.30993 ], // 3rd cluster / 3rd point
  [ 47.62490, -122.30684 ], // 2nd cluster / 1st point
  [ 47.61680, -122.34426 ], // 1th cluster / 5th point
  [ 47.62502, -122.34632 ], // 1th cluster / 4th point
  [ 47.57698, -122.32091 ], // 3rd cluster / 2nd point
  [ 47.62757, -122.30186 ], // 2nd cluster / 2nd point
  [ 47.62548, -122.34289 ], // 1st cluster / 3rd point
  [ 47.62872, -122.29053 ], // 2nd cluster / 3rd point
  [ 47.62201, -122.33551 ], // 1st cluster / 2nd point
  [ 47.58139, -122.31525 ], // 3rd cluster / 1st point
  [ 47.61947, -122.34735 ], // 1st cluster / 1st point
];

$count_of_clusters = 3;

list ($clusters, $points_by_clusters) = clusterize($points, $count_of_clusters);

var_dump($clusters);

var_dump($points_by_clusters);
--EXPECT--
array(3) {
  [0]=>
  array(3) {
    [0]=>
    float(47.578373333333)
    [1]=>
    float(-122.31536333333)
    [2]=>
    float(3)
  }
  [1]=>
  array(3) {
    [0]=>
    float(47.621756)
    [1]=>
    float(-122.343266)
    [2]=>
    float(5)
  }
  [2]=>
  array(3) {
    [0]=>
    float(47.627063333333)
    [1]=>
    float(-122.29974333333)
    [2]=>
    float(3)
  }
}
array(11) {
  [0]=>
  int(0)
  [1]=>
  int(2)
  [2]=>
  int(1)
  [3]=>
  int(1)
  [4]=>
  int(0)
  [5]=>
  int(2)
  [6]=>
  int(1)
  [7]=>
  int(2)
  [8]=>
  int(1)
  [9]=>
  int(0)
  [10]=>
  int(1)
}
