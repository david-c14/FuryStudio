cmake_minimum_required(VERSION 3.10)
project(FuryUtils VERSION 1.0)

list(APPEND REQUIRED_SRC
    dllmain.cpp 
    BinaryIO.cpp 
	Bin.cpp
	bin_c.c
    Bmp.cpp 
    bmp_c.c 
    Dat.cpp 
    dat_c.c 
    Exceptions.cpp 
    exceptions_c.c 
    Imm.cpp 
    imm_c.c 
	Lbm.cpp
	lbm_c.c
	Version.cpp
	version_c.c
)

add_library(FuryUtilsObjects OBJECT ${REQUIRED_SRC})

add_library(FuryUtils SHARED 
	$<TARGET_OBJECTS:FuryUtilsObjects>
    FuryUtils.def
)
add_library(LibFuryUtils
	$<TARGET_OBJECTS:FuryUtilsObjects>
)
if (UNIX)
	set_target_properties(LibFuryUtils PROPERTIES OUTPUT_NAME "FuryUtils") 
endif (UNIX)	
add_custom_command(TARGET FuryUtils POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "$<SHELL_PATH:$<TARGET_FILE:FuryUtils>>" "$<SHELL_PATH:${PROJECT_SOURCE_DIR}/../../UtilsDotNet/>"
)