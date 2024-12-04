cmake_minimum_required(VERSION 3.20)

project(acoustics)

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_FLAGS "-O3 -fopenmp")
find_package(LAPACK REQUIRED)

set(MAIN_EXE main.cpp)
set(READ_FILE_LIB reader.cpp)
set(FULL_MATR_LIB full_A_b.cpp)

add_library(read STATIC ${READ_FILE_LIB})
add_library(full STATIC ${FULL_MATR_LIB})

add_executable(main ${MAIN_EXE})
target_link_libraries(main read full LAPACK::LAPACK)
