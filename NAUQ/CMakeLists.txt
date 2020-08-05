cmake_minimum_required(VERSION 3.18)
project(NAUQ)

set(NAUQ_LIB nauq CACHE INTERNAL "Name of NAUQ library file")
set(NAUQ_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "Directory of NAUQ header files")
set(NAUQ_LIB_DIR ${PROJECT_BINARY_DIR} CACHE INTERNAL "Directory of NAUQ library files")

add_library(
        ${NAUQ_LIB}
        SHARED
        src/Test.cpp
)

target_include_directories(
        ${NAUQ_LIB}
        PRIVATE
        ${NAUQ_INCLUDE_DIR}
)

target_precompile_headers(
        ${NAUQ_LIB}
        PRIVATE
        [["NAUQ/nauq_pch.hpp"]]
)