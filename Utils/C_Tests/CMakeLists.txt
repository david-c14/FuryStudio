cmake_minimum_required(VERSION 3.10)
project(C_Tests VERSION 1.0)

list(APPEND REQUIRED_SRC
    catchmain.cpp
	Bin_Tests.cpp
    Bmp_Tests.cpp 
    Dat_Tests.cpp 
	Lbm_Tests.cpp
	Version_Tests.cpp
    utils.cpp 
    Wrappers.c
)

add_library(C_TestObjects OBJECT ${REQUIRED_SRC})

add_executable(C_Tests)
target_link_libraries(C_Tests FuryUtils C_TestObjects)

add_executable(C_LibTests)
target_link_libraries(C_LibTests LibFuryUtils C_TestObjects)