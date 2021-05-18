
set(NAUQ_LIB nauq CACHE INTERNAL "Name of NAUQ library file")
set(DEPEDENCE_IMGUI ${PROJECT_SOURCE_DIR}/dependence/imgui-docking)
set(DEPEDENCE_STB ${PROJECT_SOURCE_DIR}/dependence/stb_image)
set(NAUQ_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include ${DEPEDENCE_IMGUI} CACHE INTERNAL "Directory of NAUQ header files")
set(NAUQ_LIB_DIR ${PROJECT_BINARY_DIR} CACHE INTERNAL "Directory of NAUQ library files")



find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad)
#find_package(imgui CONFIG REQUIRED)

set(WINDOW_SOURCE $<IF:${UNIX},OpenGLWindow.cpp,Windows_Window.cpp>)

add_library(
        ${NAUQ_LIB}
        SHARED
        Application.cpp
        Log.cpp
        LayerStack.cpp
        OrthographicCameraController.cpp
        imGui/ImGuiLayer.cpp
        imGui/ImGuiBuild.cpp
        renderer/RenderCommand.cpp
        renderer/Renderer.cpp
        renderer/Buffer.cpp
        renderer/VertexArray.cpp
        renderer/Shader.cpp
        renderer/OrthographicCamera.cpp
        renderer/Texture.cpp
        renderer/Renderer2D.cpp
        platform/openGL/${WINDOW_SOURCE}
        platform/openGL/OpenGLInput.cpp
        platform/openGL/OpenGLContext.cpp
        platform/openGL/OpenGLBuffer.cpp
        platform/openGL/OpenGLVertexArray.cpp
        platform/openGL/OpenGLRenderAPI.cpp
        platform/openGL/OpenGLShader.cpp
        platform/openGL/OpenGLTexture.cpp
        debug/Instrumentor.cpp
        renderer/SubTexture2D.cpp
        renderer/Framebuffer.cpp
        platform/openGL/OpenGLFramebuffer.cpp
        scene/Scene.cpp
        scene/Entity.cpp ../include/nauq/renderer/Camera.hpp scene/SceneCamera.cpp ../include/nauq/scene/SceneCamera.hpp)

target_include_directories(
        ${NAUQ_LIB}
        PRIVATE
        ${NAUQ_INCLUDE_DIR}
        ${DEPEDENCE_IMGUI}
        ${DEPEDENCE_STB}
        ${ENTT_INCLUDE_DIR}
)

message(STATUS ${ENTT_INCLUDE_DIR})


#target_link_directories(
#        ${NAUQ_LIB}
#        PRIVATE
#        ${IMGUI_DOCKING_LIB_DIR}
#)


target_link_libraries(
        ${NAUQ_LIB}
        PRIVATE
        spdlog::spdlog
        spdlog::spdlog_header_only
        GL
        glfw
#        glm
        glad::glad
        imgui-docking
        stb_image
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
        NQ_ENABLE_ASSERTS
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
            NQ_PLATFORM_WINDOWS
            PRIVATE
            NAUQ_BUILD_DLL
    )
endif ()