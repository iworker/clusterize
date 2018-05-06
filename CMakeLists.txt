cmake_minimum_required(VERSION 3.8)
project(clusterize)

add_custom_target(makefile COMMAND phpize && ./configure && make && make install
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES clusterize
        clusterize.c
        points.c
        kmeans.c)


set(PHP_SOURCE $(php-config --include-dir))
include_directories(${PHP_SOURCE}/main)
include_directories(${PHP_SOURCE}/Zend)
include_directories(${PHP_SOURCE}/sapi)
include_directories(${PHP_SOURCE}/pear)
include_directories(${PHP_SOURCE}/TSRM)
include_directories(${PHP_SOURCE})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(clusterize ${SOURCE_FILES})
