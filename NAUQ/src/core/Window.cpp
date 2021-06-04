//
// Created by nauq302 on 04/06/2021.
//
#include "nauq/core/Window.hpp"
#include "nauq/renderer/Renderer.hpp"

#ifdef NQ_PLATFORM_OPENGL
    #include "nauq/platform/openGL/OpenGLWindow.hpp"
    #define CREATE_OPENGL_WINDOW(props) createScope<OpenGLWindow>(props)
#else
    #define CREATE_OPENGL_WINDOW(props) (NQ_ERROR("OpenGL not supported"), nullptr)
#endif

#ifdef NQ_PLATFORM_VULKAN
    #include "nauq/platform/vulkan/VulkanWindow.hpp"
    #define CREATE_VULKAN_WINDOW(props) createScope<OpenGLWindow>(props)
#else
    #define CREATE_VULKAN_WINDOW(props) (NQ_ERROR("Vulkan not supported"), nullptr)
#endif


namespace nauq {
    /**
     *
     * @param props
     * @return
     */
    Scope<Window> Window::create(const WindowProps& props)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::OPEN_GL:
                return CREATE_OPENGL_WINDOW(props);
            default:
                return nullptr;
        }

    }

}