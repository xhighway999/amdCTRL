cmake_minimum_required(VERSION 3.0)
project(AmdCtrl)

add_subdirectory(imguiappfoundation)
add_subdirectory(src)

set (CMAKE_CXX_STANDARD 17)

add_executable(AmdCtrl main.cpp)
target_link_libraries(AmdCtrl core src)

if(${DevMode})
    target_compile_definitions(AmdCtrl PUBLIC DEV)
    #Link the dev tools dependency
    target_link_libraries(AmdCtrl devtools)
endif()

