cmake_minimum_required(VERSION 3.10)
project(Cpp_Samples VERSION 1.0)
add_executable(Cpp_Samples
    main.cpp
	bmp2imm.cpp
	imm2bmp.cpp
	dat_create.cpp
	dat_read.cpp
)
target_link_libraries(Cpp_Samples FuryUtils)