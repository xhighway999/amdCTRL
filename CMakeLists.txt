cmake_minimum_required(VERSION 3.0)
project(AmdCtrl)

add_subdirectory(xhfr)
add_subdirectory(src)

set (CMAKE_CXX_STANDARD 17)

add_executable(AmdCtrl main.cpp)
target_link_libraries(AmdCtrl xhfr src)
