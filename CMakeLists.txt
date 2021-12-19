cmake_minimum_required(VERSION 3.3)
project(msp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(msp main.c msp_include/msp_vector/msp_vector.h msp_include/msp_vector/msp_vector.c msp_include/msp_matrix/msp_matrix.h
        msp_include/msp_matrix/msp_matrix.c msp_include/msp_complex/msp_complex.c msp_include/msp_complex/msp_complex.h
        msp_include/msp_logger/msp_log.h msp_include/msp_logger/msp_log.c msp_include/msp_matrix/msp_matrix_complex.h msp_include/msp_matrix/msp_matrix_complex.c
        msp_include/msp_vector/msp_vector_complex.h msp_include/msp_vector/msp_vector_complex.c)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

#include_directories(${GTK3_INCLUDE_DIRS})
#link_directories(${GTK3_LIBRARY_DIRS})

#add_definitions(${GTK3_CFLAGS_OTHER})

#target_link_libraries(msp ${GTK3_LIBRARIES})