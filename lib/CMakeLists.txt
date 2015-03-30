# build using
# mkdir build
# cd build
# cmake -G "MSYS Makefiles" ../  # for Windows

PROJECT(libbbn-ni-r)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_DEFINITIONS(${CMAKE_CXX_FLAGS} "-std=c++11")

SET (SHARED_LIBRARY_SOURCE libbbn-ni-r.cpp NiFpga.c)

ADD_LIBRARY(bbn-ni-r SHARED ${SHARED_LIBRARY_SOURCE})
