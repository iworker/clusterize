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

$expected_clusters = [
  [ 47.578373, -122.315363, 3 ],
  [ 47.621756, -122.343266, 5 ],
  [ 47.627063, -122.299743, 3 ],
];

$success = 0;

foreach ($clusters as $cluster) {
  foreach ($expected_clusters as $expected_cluster) {
    if (abs($cluster[0] - $expected_cluster[0]) < 0.0001 && 
        abs($cluster[1] - $expected_cluster[1]) < 0.0001 && 
        $cluster[2] == $expected_cluster[2]) {
      ++$success;
      break;
    }
  }
}

// success equals 3 means that all 3 expected points found in result clusters
var_dump($success);

// all these checks equals true means that all the points are in the correct cluster
var_dump(($points_by_clusters[0] === $points_by_clusters[4]) &&
         ($points_by_clusters[4] === $points_by_clusters[9]));

var_dump(($points_by_clusters[1] === $points_by_clusters[5]) &&
         ($points_by_clusters[5] === $points_by_clusters[7]));

var_dump(($points_by_clusters[2] === $points_by_clusters[3]) &&
         ($points_by_clusters[3] === $points_by_clusters[6]) &&
         ($points_by_clusters[6] === $points_by_clusters[8]) &&
         ($points_by_clusters[8] === $points_by_clusters[10]));

--EXPECT--
int(3)
bool(true)
bool(true)
bool(true)
