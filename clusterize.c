#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define HAVE_CLUSTERIZE 1

#include "php.h"
#include "clusterize.h"
#include "points.h"

#if HAVE_CLUSTERIZE

#define PHP_CLUSTERIZE_VERSION "1.0"
#define PHP_CLUSTERIZE_EXTNAME "clusterize"

extern zend_module_entry clusterize_module_entry;
#define phpext_clusterize_ptr &clusterize_module_entry

PHP_FUNCTION(clusterize);

static zend_function_entry clusterize_functions[] = {
    PHP_FE(clusterize, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry clusterize_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_CLUSTERIZE_EXTNAME,
    clusterize_functions,
    NULL, // name of the MINIT function or NULL if not applicable
    NULL, // name of the MSHUTDOWN function or NULL if not applicable
    NULL, // name of the RINIT function or NULL if not applicable
    NULL, // name of the RSHUTDOWN function or NULL if not applicable
    NULL, // name of the MINFO function or NULL if not applicable
#if ZEND_MODULE_API_NO >= 20010901
    PHP_CLUSTERIZE_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(clusterize);

PHP_FUNCTION(clusterize)
{
  zval *source_vectors;
  zval *clusters_count;

  if (zend_parse_parameters(2 TSRMLS_CC, "al", &source_vectors, &clusters_count) == FAILURE) {
    RETURN_FALSE;
  }

  uint32_t n = Z_ARRVAL_P(source_vectors)->nNumOfElements;

  Point *points = (Point *) ecalloc(n, sizeof(Point));

  for (uint32_t i = 0; i < n; ++i)
  {
    convert_to_double(&Z_ARRVAL(Z_ARRVAL_P(source_vectors)->arData[i].val)->arData[0].val);
    convert_to_double(&Z_ARRVAL(Z_ARRVAL_P(source_vectors)->arData[i].val)->arData[1].val);

    points[i].x = Z_DVAL(Z_ARRVAL(Z_ARRVAL_P(source_vectors)->arData[i].val)->arData[0].val);
    points[i].y = Z_DVAL(Z_ARRVAL(Z_ARRVAL_P(source_vectors)->arData[i].val)->arData[1].val);
  }

  kmeans_config config;
  kmeans_result result;

  config.k = (uint32_t) clusters_count;
  config.num_objs = n;
  config.max_iterations = 200;
  config.distance_method = pt_distance;
  config.centroid_method = pt_centroid;

  config.objs = ecalloc(config.num_objs, sizeof(Pointer));
  config.centers = ecalloc(config.k, sizeof(Pointer));
  config.clusters = ecalloc(config.num_objs, sizeof(int));
  config.clusters_sizes = ecalloc(config.k, sizeof(int));
  Point *init = ecalloc(config.k, sizeof(Point));

  int i;

  for (i = 0; i < config.num_objs; ++i)
  {
    config.objs[i] = &(points[i]);
  }

  int part_size = lroundf(config.num_objs / config.k);

  for (i = 0; i < config.k; ++i)
  {
    int r = i * part_size + lround(part_size * (1.0 * rand() / RAND_MAX));

    init[i] = points[r];

    config.centers[i] = &(init[i]);
  }

  result = kmeans(&config);

  if (result == KMEANS_ERROR)
  {
    efree(points);
    efree(init);
    efree(config.objs);
    efree(config.centers);
    efree(config.clusters);
    efree(config.clusters_sizes);

    RETURN_FALSE;
  }

  array_init_size(return_value, 2);

  zval clusters;

  array_init_size(&clusters, config.k);

  for (i = 0; i < config.k; ++i)
  {
    zval *cluster_center = emalloc(sizeof(zval *));
    array_init_size(cluster_center, 3);

    add_next_index_double(cluster_center, init[i].x);
    add_next_index_double(cluster_center, init[i].y);
    add_next_index_double(cluster_center, config.clusters_sizes[i]);

    add_next_index_zval(&clusters, cluster_center);

    efree(cluster_center);
  }

  add_next_index_zval(return_value, &clusters);

  zval values;

  array_init_size(&values, config.num_objs);

  for (i = 0; i < config.num_objs; ++i)
  {
    add_next_index_long(&values, config.clusters[i]);
  }

  add_next_index_zval(return_value, &values);

  efree(points);
  efree(init);
  efree(config.objs);
  efree(config.centers);
  efree(config.clusters);
  efree(config.clusters_sizes);

  RETURN_ZVAL(return_value, 0, 0);
}

#endif
