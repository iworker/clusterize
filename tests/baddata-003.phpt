--TEST--
Test some bad input
--FILE--
<?php

var_dump(clusterize(null, null));
var_dump(clusterize(null, 5));
var_dump(clusterize(5, null));
var_dump(clusterize("", 0));
var_dump(clusterize(false, 1));
var_dump(clusterize(true, 1));
var_dump(clusterize([], 1));
var_dump(clusterize([[]], 1));
var_dump(clusterize([[[],[]]], 2));
var_dump(clusterize([[2]], 2));
var_dump(clusterize([[2, 5]], 5));
var_dump(clusterize([[ 5 => 2, 6 => 3 ]], 2));

--EXPECTF--
Warning: clusterize() expects parameter 1 to be array, %s given in %s
bool(false)

Warning: clusterize() expects parameter 1 to be array, %s given in %s
bool(false)

Warning: clusterize() expects parameter 1 to be array, %s given in %s
bool(false)

Warning: clusterize() expects parameter 1 to be array, %s given in %s
bool(false)

Warning: clusterize() expects parameter 1 to be array, %s given in %s
bool(false)

Warning: clusterize() expects parameter 1 to be array, %s given in %s
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)