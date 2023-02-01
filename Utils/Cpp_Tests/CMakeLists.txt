cmake_minimum_required(VERSION 3.10)
project(Cpp_Tests VERSION 1.0)
add_library(Cpp_Tests SHARED 
    Bmp_Tests.cpp 
    Bmp2Imm_Tests.cpp 
    Dat_Tests.cpp 
    Imm2Bmp_Tests.cpp 
    utils.cpp
)
target_link_libraries(Cpp_Tests FuryUtils)