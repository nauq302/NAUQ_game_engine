cmake_minimum_required(VERSION 3.18)
project(NAUQ)

set(NAUQ_LIB nauq CACHE INTERNAL "Name of NAUQ library file")
set(NAUQ_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "Directory of NAUQ header files")
set(NAUQ_LIB_DIR ${PROJECT_BINARY_DIR} CACHE INTERNAL "Directory of NAUQ library files")

find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

set(WINDOW_SOURCE $<IF:$<CXX_COMPILER_ID:MSVC>,Windows_Window.cpp,Linux_Window.cpp>)

message(STATUS ${WINDOW_SOURCE})

add_library(
        ${NAUQ_LIB}
        SHARED
        src/Application.cpp
        src/Log.cpp
        src/platform/${WINDOW_SOURCE}
)

target_include_directories(
        ${NAUQ_LIB}
        PRIVATE
        ${NAUQ_INCLUDE_DIR}
)

target_link_libraries(
        ${NAUQ_LIB}
        PRIVATE
        spdlog::spdlog
        spdlog::spdlog_header_only
        GL
        glfw
        glm
)

target_precompile_headers(
        ${NAUQ_LIB}
        PRIVATE
        [["nauq/nauq_pch.hpp"]]
)

get_target_property(NAUQ_INCLUDE_DIR ${NAUQ_LIB} INCLUDE_DIRECTORIES)

message(STATUS ${NAUQ_INCLUDE_DIR})

if (MSVC)
    target_compile_definitions(
            ${NAUQ_LIB}
            PUBLIC
            NAUQ_PLATFORM_WINDOWS
            PRIVATE
            NAUQ_BUILD_DLL
    )
endif ()