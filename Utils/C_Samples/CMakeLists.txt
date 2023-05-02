cmake_minimum_required(VERSION 3.10)
project(C_Samples VERSION 1.0)
add_executable(C_Samples
    main.c
	imm2bmp.c
)
target_link_libraries(C_Samples FuryUtils)