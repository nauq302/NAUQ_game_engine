
set(NAUQ_LIB nauq CACHE INTERNAL "Name of NAUQ library file")
set(DEPEDENCE_IMGUI ${PROJECT_SOURCE_DIR}/dependence/imgui-docking)
set(NAUQ_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include ${DEPEDENCE_IMGUI} CACHE INTERNAL "Directory of NAUQ header files")
set(NAUQ_LIB_DIR ${PROJECT_BINARY_DIR} CACHE INTERNAL "Directory of NAUQ library files")



find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad)
#find_package(imgui CONFIG REQUIRED)

set(WINDOW_SOURCE $<IF:${UNIX},Glfw3_Window.cpp,Windows_Window.cpp>)

add_library(
        ${NAUQ_LIB}
        SHARED
        Application.cpp
        Log.cpp
        platform/glfw3/${WINDOW_SOURCE}
        platform/glfw3/Glfw3_Input.cpp
        Layer.cpp
        LayerStack.cpp
        imGui/ImGuiLayer.cpp
        imGui/ImGuiBuild.cpp
        ../include/nauq/imGui/ImGuiImpl.hpp)

target_include_directories(
        ${NAUQ_LIB}
        PRIVATE
        ${NAUQ_INCLUDE_DIR}
        ${DEPEDENCE_IMGUI}
)

#target_link_directories(
#        ${NAUQ_LIB}
#        PRIVATE
#        ${IMGUI_DOCKING_LIB_DIR}
#)

message(STATUS ${IMGUI_DOCKING_LIB_DIR})

target_link_libraries(
        ${NAUQ_LIB}
        PRIVATE
        spdlog::spdlog
        spdlog::spdlog_header_only
        GL
        glfw
        glm
        glad::glad
        imgui-docking
#        imgui::imgui
)

target_precompile_headers(
        ${NAUQ_LIB}
        PRIVATE
        "nauq_pch.hpp"
)

target_compile_definitions(
        ${NAUQ_LIB}
        PUBLIC
        NAUQ_ENABLE_ASSERTS
        GLFW_INCLUDE_NONE
)

target_compile_options(
        ${NAUQ_LIB}
        PRIVATE
        -fpic
)


if (MSVC)
    target_compile_definitions(
            ${NAUQ_LIB}
            PUBLIC
            NAUQ_PLATFORM_WINDOWS
            PRIVATE
            NAUQ_BUILD_DLL
    )
endif ()