/*-------------------------------------------------------------------------
 *
 * kmeans.c
 *    Generic k-means implementation
 *
 * Copyright (c) 2016, Paul Ramsey <pramsey@cleverelephant.ca>
 *
 *------------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>

#include "kmeans.h"

static void update_r(kmeans_config *config)
{
  int i;

  for (i = 0; i < config->num_objs; ++i)
  {
    double distance, curr_distance;
    int cluster, curr_cluster;
    Pointer obj;

    obj = config->objs[i];

    /*
     * Don't try to cluster NULL objects, just add them
     * to the "unclasterable cluster"
     */
    if (!obj)
    {
      config->clusters[i] = KMEANS_NULL_CLUSTER;
      continue;
    }

    /* Initialize with distance to first cluster */
    curr_distance = (config->distance_method)(obj, config->centers[0]);
    curr_cluster  = 0;

    /* Check all other cluster centers and find the nearest */
    for (cluster = 1; cluster < config->k; ++cluster)
    {
      distance = (config->distance_method)(obj, config->centers[cluster]);

      if (distance < curr_distance)
      {
        curr_distance = distance;
        curr_cluster  = cluster;
      }
    }

    /* Store the nearest cluster this object is in */
    config->clusters[i] = curr_cluster;
    config->clusters_sizes[curr_cluster] += 1;
  }
}

static void update_means(kmeans_config *config)
{
  int i;

  for (i = 0; i < config->k; ++i)
  {
    /* Update the centroid for this cluster */
    (config->centroid_method)(config->objs, config->clusters, config->num_objs, i, config->centers[i]);
  }
}

kmeans_result kmeans(kmeans_config *config)
{
  int iterations = 0;
  int *clusters_last;
  size_t clusters_sz = sizeof(int) * config->num_objs;
  size_t clusters_size_sz = sizeof(int) * config->k;

  if (config->k > config->num_objs)
  {
    return KMEANS_ERROR;
  }

  /* Zero out cluster numbers, just in case user forgets */
  memset(config->clusters, 0, clusters_sz);

  /* Set default max iterations if necessary */
  if (!config->max_iterations)
  {
    config->max_iterations = KMEANS_MAX_ITERATIONS;
  }

  /*
   * Previous cluster state array. At this time, r doesn't mean anything
   * but it's ok
   */
  clusters_last = kmeans_malloc(clusters_sz);

  while(1)
  {
    /* Store the previous state of the clustering */
    memcpy(clusters_last, config->clusters, clusters_sz);
    memset(config->clusters_sizes, 0, clusters_size_sz);

    update_r(config);
    update_means(config);

    /*
     * if all the cluster numbers are unchanged since last time,
     * we are at a stable solution, so we can stop here
     */
    if (memcmp(clusters_last, config->clusters, clusters_sz) == 0)
    {
      kmeans_free(clusters_last);
      config->total_iterations = (unsigned int) iterations;
      return KMEANS_OK;
    }

    if (iterations++ > config->max_iterations)
    {
      kmeans_free(clusters_last);
      config->total_iterations = (unsigned int) iterations;
      return KMEANS_EXCEEDED_MAX_ITERATIONS;
    }
  }
}
