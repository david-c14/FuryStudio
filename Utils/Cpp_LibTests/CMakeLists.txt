cmake_minimum_required(VERSION 3.10)
project(Cpp_LibTests VERSION 1.0)
add_executable(Cpp_LibTests
	catchmain.cpp
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
target_link_libraries(Cpp_LibTests LibFuryUtils)