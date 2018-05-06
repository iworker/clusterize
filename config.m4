PHP_ARG_ENABLE(clusterize, clusterize module,
[  --enable-clusterize        Enable clusterize module.])

if test "$PHP_CLUSTERIZE" != "no"; then
  AC_DEFINE(HAVE_CLUSTERIZE, 1, [Have CLUSTERIZE library])
  PHP_NEW_EXTENSION(clusterize, clusterize.c kmeans.c points.c, $ext_shared)
fi

