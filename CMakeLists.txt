cmake_minimum_required(VERSION 3.23)
project(poolmemory)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${PROJECT_SOURCE_DIR}/examples)
#add_subdirectory(${PROJECT_SOURCE_DIR}/lib_src)
add_executable(poolmemory main.cpp)

