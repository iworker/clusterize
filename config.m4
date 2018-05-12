PHP_ARG_ENABLE(clusterize, clusterize module,
[  --enable-clusterize        Enable clusterize module])

if test "$PHP_CLUSTERIZE" != "no"; then
  AC_DEFINE(HAVE_CLUSTERIZE, 1, [Have CLUSTERIZE library])
  PHP_NEW_EXTENSION(clusterize, clusterize.c kmeans.c points.c, $ext_shared)
fi

PHP_ARG_ENABLE(coverage, enable code coverage,
[  --enable-coverage        Enable developer code coverage information [default=no])

if test "$PHP_COVERAGE" = "yes"; then
  PHP_CHECK_GCC_ARG(-fprofile-arcs,                     COVERAGE_CFLAGS="$COVERAGE_CFLAGS -fprofile-arcs")
  PHP_CHECK_GCC_ARG(-ftest-coverage,                    COVERAGE_CFLAGS="$COVERAGE_CFLAGS -ftest-coverage")
  EXTRA_LDFLAGS="$COVERAGE_CFLAGS"
fi
