cmake_minimum_required(VERSION 3.16)
project(NAUQ_game_engine_Editor)


find_package(spdlog CONFIG REQUIRED)


add_executable(editor EditorApp.cpp Editor2DLayer.cpp panel/SceneHierarchyPanel.cpp panel/SceneHierarchyPanel.hpp)


target_include_directories(editor PRIVATE ${NAUQ_INCLUDE_DIR})
message(STATUS ${IMGUI_DOCKING_LIB_DIR})
target_link_directories(editor PRIVATE ${IMGUI_DOCKING_LIB_DIR})
target_link_directories(editor PRIVATE ${NAUQ_LIB_DIR} imgui-docking)

target_link_libraries(editor PRIVATE ${NAUQ_LIB} spdlog::spdlog spdlog::spdlog_header_only)



target_precompile_headers(editor PRIVATE [[Editor_pch.hpp]])


if (MSVC)
    add_custom_command(
            TARGET demo POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${NAUQ_LIB}.dll ${PROJECT_BINARY_DIR}
            COMMENT "Copy dll file to exe dir"
    )
endif ()