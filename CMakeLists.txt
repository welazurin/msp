include(msp_include/CMakeLists.txt)


cmake_minimum_required(VERSION 3.3)
project(msp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(msp ${msp} main.c)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

#include_directories(${GTK3_INCLUDE_DIRS})
#link_directories(${GTK3_LIBRARY_DIRS})

#add_definitions(${GTK3_CFLAGS_OTHER})

#target_link_libraries(msp ${GTK3_LIBRARIES})