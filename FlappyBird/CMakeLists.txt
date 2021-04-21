cmake_minimum_required(VERSION 3.16)
project(NAUQ_game_engine_FlappyBird)


find_package(spdlog CONFIG REQUIRED)

add_executable(flappyBird app.cpp GameLayer.cpp GameLayer.hpp Random.hpp Level.cpp Level.hpp Player.cpp Player.hpp Color.hpp)

target_include_directories(flappyBird PRIVATE ${NAUQ_INCLUDE_DIR})

target_link_directories(flappyBird PRIVATE ${NAUQ_LIB_DIR})

target_link_libraries(flappyBird PRIVATE ${NAUQ_LIB} spdlog::spdlog spdlog::spdlog_header_only)

if (MSVC)
    add_custom_command(
            TARGET flappyBird POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${NAUQ_LIB}.dll ${PROJECT_BINARY_DIR}
            COMMENT "Copy dll file to exe dir"
    )
endif ()