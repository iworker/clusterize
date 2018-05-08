/*-------------------------------------------------------------------------
 *
 * kmeans.c
 *    Generic k-means implementation
 *
 * Copyright (c) 2016, Paul Ramsey <pramsey@cleverelephant.ca>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
