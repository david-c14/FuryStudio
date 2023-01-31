cmake_minimum_required(VERSION 3.10)
project(C_Tests VERSION 1.0)
add_library(C_Tests SHARED Bmp_Tests.cpp Dat_Tests.cpp utils.cpp Wrappers.c)
target_link_libraries(C_Tests FuryUtils)