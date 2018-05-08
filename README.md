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
