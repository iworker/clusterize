cmake_minimum_required(VERSION 3.8)
project(clusterize)

add_custom_target(makefile COMMAND phpize && ./configure && make && make install
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES php_clusterize
        php_clusterize.c
        points.c
        kmeans.c)

execute_process (
        COMMAND php-config --include-dir
        OUTPUT_VARIABLE PHP_SOURCE
)

# set(PHP_SOURCE /usr/local/Cellar/php/7.2.4_1/include/php)

include_directories(${PHP_SOURCE}/main)
include_directories(${PHP_SOURCE}/Zend)
include_directories(${PHP_SOURCE}/sapi)
include_directories(${PHP_SOURCE}/pear)
include_directories(${PHP_SOURCE}/TSRM)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(clusterize ${SOURCE_FILES})
