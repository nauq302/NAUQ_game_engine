cmake_minimum_required(VERSION 3.16)

project(stb_image)

add_library(stb_image OBJECT stb_image.cpp)

set(STB_IMAGE_LIB_DIR ${PROJECT_BINARY_DIR} CACHE INTERNAL "Directory of NAUQ library files")

target_compile_options(
        stb_image
        PRIVATE
        -fPIC
)