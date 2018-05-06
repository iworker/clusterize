/*-------------------------------------------------------------------------
 *
 * kmeans.h
 *    Generic k-means implementation
 *
 * Copyright (c) 2016, Paul Ramsey <pramsey@cleverelephant.ca>
 *
 *------------------------------------------------------------------------*/

#ifndef KMEANS_H
#define KMEANS_H

#include <stdlib.h>

/*
 * When clustering lists with NULL elements, they will get this as
 * their cluster number. (All the other clusters will be non-negative)
 */
#define KMEANS_NULL_CLUSTER -1

/*
 * If the algorithm doesn't converge within this number of iterations,
 * it will return with a failure error code.
 */
#define KMEANS_MAX_ITERATIONS 1000

#define kmeans_malloc(size) malloc(size)
#define kmeans_free(ptr) free(ptr)

typedef void* Pointer;

typedef enum {
        KMEANS_OK,
        KMEANS_EXCEEDED_MAX_ITERATIONS,
        KMEANS_ERROR
} kmeans_result;

/*
 * Prototype for the distance calculating function
 */
typedef double (*kmeans_distance_method) (const Pointer a, const Pointer b);

/*
 * Prototype for the centroid calculating function
 * @param objs the list of all objects in the calculation
 * @param clusters the list of cluster numbers for each object
 * @param num_objs the number of objects/cluster numbers in the previous arrays
 * @param cluster the cluster number we are actually generating a centroid for here
 * @param centroid the object to write the centroid result into (already allocated)
 */
typedef void (*kmeans_centroid_method) (const Pointer *objs, const int *clusters, size_t num_objs, int cluster, Pointer centroid);

typedef struct kmeans_config
{
  /* Function returns the "distance" between any pair of objects */
  kmeans_distance_method distance_method;

  /* Function returns the "centroid" of a collection of objects */
  kmeans_centroid_method centroid_method;

  /*
   * An array of objects to be analyzed. User allocates this array
   * and is responsible for freeing it.
   * For objects that are not capable of participating in the distance
   * calculations, but for which you still want included in the process
   * (for examples, database nulls, or geometry empties) use a NULL
   * value in this list. All NULL values will be returned in the
   * KMEANS_NULL_CLUSTER.
   */
  Pointer *objs;

  /* Number of objects in the preceding array */
  size_t num_objs;

  /*
   * An array of initial centers for the algorithm
   * Can be randomly assigned, or using proportions,
   * unfortunately the algorithm is sensitive to starting
   * point, so using "better" set of starting points
   * might be wise. User allocates and is responsible for freeing
   */
  Pointer *centers;

  /* Number of means we are calculating, length of preceding array */
  unsigned int k;

  /*
   * Maximum number of times to iterate the algorithm, or 0 for
   * library default
   */
  unsigned int max_iterations;

  /* Iteration counter */
  unsigned int total_iterations;

  /* Array to fill in with cluster numbers. User allocates and frees. */
  int *clusters;

  int *clusters_sizes;
} kmeans_config;

/* This is where the magic happens. */
kmeans_result kmeans(kmeans_config *config);

#endif
