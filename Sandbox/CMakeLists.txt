cmake_minimum_required(VERSION 3.18)
project(NAUQ_game_engine_Sandbox)


find_package(spdlog CONFIG REQUIRED)

add_executable(demo SandboxApp.cpp)
target_include_directories(demo PRIVATE ${NAUQ_INCLUDE_DIR})
target_link_directories(demo PRIVATE ${NAUQ_LIB_DIR})
target_link_libraries(demo PRIVATE ${NAUQ_LIB} spdlog::spdlog spdlog::spdlog_header_only)

if (MSVC)
    add_custom_command(
            TARGET demo POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${NAUQ_LIB}.dll ${PROJECT_BINARY_DIR}
            COMMENT "Copy dll file to exe dir"
    )
endif ()