
set(NAUQ_LIB nauq CACHE INTERNAL "Name of NAUQ library file")
set(NAUQ_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "Directory of NAUQ header files")
set(NAUQ_LIB_DIR ${PROJECT_BINARY_DIR} CACHE INTERNAL "Directory of NAUQ library files")

set(DEPEDENCE_IMGUI ${PROJECT_SOURCE_DIR}/dependence/imgui)

find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad)
find_package(imgui CONFIG REQUIRED)

set(WINDOW_SOURCE $<IF:${UNIX},Linux_Window.cpp,Windows_Window.cpp>)

add_library(
        ${NAUQ_LIB}
        SHARED
        Application.cpp
        Log.cpp
        platform/linux/${WINDOW_SOURCE}
        platform/linux/Linux_Input.cpp
        Layer.cpp
        LayerStack.cpp
        imGui/ImGuiLayer.cpp
        ${DEPEDENCE_IMGUI}/imgui_impl_opengl3.cpp
        ${DEPEDENCE_IMGUI}/imgui_impl_glfw.cpp
        )

target_include_directories(
        ${NAUQ_LIB}
        PRIVATE
        ${NAUQ_INCLUDE_DIR}
        ${DEPEDENCE_IMGUI}
)

target_link_libraries(
        ${NAUQ_LIB}
        PRIVATE
        spdlog::spdlog
        spdlog::spdlog_header_only
        GL
        glfw
        glm
        glad::glad
        imgui::imgui
)

target_precompile_headers(
        ${NAUQ_LIB}
        PRIVATE
        [["nauq/nauq_pch.hpp"]]
)

target_compile_definitions(
        ${NAUQ_LIB}
        PUBLIC
        NAUQ_ENABLE_ASSERTS
        GLFW_INCLUDE_NONE
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