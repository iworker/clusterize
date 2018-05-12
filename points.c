#include "points.h"

double pt_distance(const Pointer a, const Pointer b)
{
  Point *pa, *pb;
  double dx, dy;

  pa = (Point*) a;
  pb = (Point*) b;

  dx = (pa->x - pb->x);
  dy = (pa->y - pb->y);

  return dx * dx + dy * dy;
}

void pt_centroid(const Pointer *objs, const int *clusters, size_t num_objs, int cluster, Pointer centroid)
{
  int i;
  int num_cluster;
  Point sum, **pts, *center;

  pts = (Point**) objs;
  center = (Point*) centroid;

  sum.x = sum.y = 0.0;

  if (num_objs <= 0) {
    return;
  }

  num_cluster = 0;

  for (i = 0; i < num_objs; ++i)
  {
    if (clusters[i] != cluster) {
      continue;
    }

    sum.x += pts[i]->x;
    sum.y += pts[i]->y;

    ++num_cluster;
  }

  if (num_cluster)
  {
    sum.x /= num_cluster;
    sum.y /= num_cluster;
    *center = sum;
  }
}
