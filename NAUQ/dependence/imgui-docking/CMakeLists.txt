cmake_minimum_required(VERSION 3.16)

project(imgui-docking)

find_package(glfw3 REQUIRED)

add_library(imgui-docking
        imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_widgets.cpp
        misc/cpp/imgui_stdlib.cpp
        misc/fonts/binary_to_compressed_c.cpp
        misc/freetype/imgui_freetype.cpp
        )

target_link_libraries(
        imgui-docking
        PRIVATE
        glfw
)

target_include_directories(
        imgui-docking
        PRIVATE
        ${PROJECT_SOURCE_DIR}
)

target_compile_options(
        imgui-docking
        PRIVATE
        -fPIC
)

set(IMGUI_DOCKING_LIB_DIR ${PROJECT_BINARY_DIR} CACHE INTERNAL "Directory of NAUQ library files")
