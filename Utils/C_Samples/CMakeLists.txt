cmake_minimum_required(VERSION 3.10)
project(C_Samples VERSION 1.0)
add_executable(C_Samples
    main.c
	bmp2imm.c
	imm2bmp.c
	dat_create.c
	dat_read.c
)
if (MSVC) 
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif (MSVC)
target_link_libraries(C_Samples FuryUtils)