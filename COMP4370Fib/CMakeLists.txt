cmake_minimum_required(VERSION 3.19)
project(assignment3)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
        )
include(CompilerSetup)
include(GetGoogletest)
colorize_output()

set(CMAKE_CXX_STANDARD 17)


add_executable(COMP4370Ass2MergFib main.cpp MergeSort.cpp MergeSort.h Fibonacci.cpp Fibonacci.h Vectors.cpp Vectors.h)

enable_warnings_for(assignment3)

add_subdirectory(tests)