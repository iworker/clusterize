#ifndef POINTS_H
#define POINTS_H

#include "kmeans.h"

typedef struct Point
{
    double x;
    double y;
} Point;

double pt_distance(const Pointer a, const Pointer b);
void pt_centroid(const Pointer *objs, const int *clusters, size_t num_objs, int cluster, Pointer centroid);

#endif
