cmake_minimum_required(VERSION 3.31)
project(cpp_random_forest)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)

add_executable(cpp_random_forest main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(cpp_random_forest PRIVATE OpenMP::OpenMP_CXX)
endif()
