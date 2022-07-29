cmake_minimum_required(VERSION 3.16)
project(my_test VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# tensorflow include
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib_srcs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-as-needed -ldl -pthread")

add_executable(main main.cpp)