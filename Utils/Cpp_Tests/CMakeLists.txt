cmake_minimum_required(VERSION 3.10)
project(Cpp_Tests VERSION 1.0)

list(APPEND REQUIRED_SRC
	catchmain.cpp
	Bin_Tests.cpp
    Bmp_Tests.cpp 
    Bmp2Imm_Tests.cpp 
	Bmp2Lbm_Tests.cpp
    Dat_Tests.cpp 
    Imm2Bmp_Tests.cpp 
    Lbm_Tests.cpp
	Lbm2Bmp_Tests.cpp
    Version_Tests.cpp
    utils.cpp
)

add_library(Cpp_TestObjects OBJECT ${REQUIRED_SRC})

add_executable(Cpp_Tests)
target_link_libraries(Cpp_Tests FuryUtils Cpp_TestObjects)

add_executable(Cpp_LibTests)
target_link_libraries(Cpp_LibTests LibFuryUtils Cpp_TestObjects)