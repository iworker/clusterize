[![Build Status](https://travis-ci.org/iworker/clusterize.svg?branch=master)](https://travis-ci.org/iworker/clusterize)

# clusterize
PHP extension for clustering points on GEO map

# Installation

1. Compile extension:
```
git clone git@github.com:iworker/clusterize.git
cd clusterize
phpize
./configure --enable-clusterize
make
sudo make install
```
2. Add to php.ini:
```
extension=clusterize.so
```

# kmeans
K-Means algorithm based on https://github.com/pramsey/kmeans/ library

# usage

### simple example

```
$points = [ [ 10, 10], [ 12, 12 ], [ 30, 30 ], [ 32, 32 ] ];
$count_of_clusters = 2;
 
list ($clusters, $points_by_clusters) = clusterize($points, $count_of_clusters);
```

`$clusters`:
```
[ [ 11, 11, 2 ], [ 31, 31, 2 ]];
```

`$points_by_clusters`:
```
[ 0, 0, 1, 1 ]
```

### real life example

Let's imagine that there are 3 clusters of points on map in Seattle:

[![3 clusters in Seattle](https://raw.githubusercontent.com/iworker/clusterize/assets/map001.png)](https://drive.google.com/open?id=1JEVJFMpGEaF5nYbsBms7J_ZDLtSMR8of&usp=sharing)

Our goal is to detect these 3 clusters using clusterize function:

```
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
```

`$clusters`:
```
[
  [ 47.578373, -122.315363, 3 ],
  [ 47.621756, -122.343266, 5 ],
  [ 47.627063, -122.299743, 3 ],
]
```

`$points_by_clusters`:
```
[0, 2, 1, 1, 0, 2, 1, 2, 1, 0, 1]
```

So, points divided into 3 clusters:
 - cluster with index 0 which corresponds 3rd cluster on map
 - cluster with index 1 which corresponds 1st cluster on map
 - cluster with index 2 which corresponds 2nd cluster on map 
