cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Cli_Tests VERSION 1.0)
add_executable(Cli_Tests
    catchmain.cpp
    Dat_Tests.cpp 
    Imm_Tests.cpp 
)
