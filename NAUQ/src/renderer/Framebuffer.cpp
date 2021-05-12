//
// Created by nauq302 on 07/05/2021.
//

#include "nauq/renderer/Framebuffer.hpp"
#include "nauq/renderer/Renderer.hpp"
#include "nauq/platform/openGL/OpenGLFramebuffer.hpp"

namespace nauq {


    Ref<Framebuffer> Framebuffer::create(const FramebufferSpecification& spec)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE: NQ_CORE_ASSERT(false, "RendererAPI::NONE is not currently supported!"); return nullptr;
            case RendererAPI::API::OPEN_GL: return createRef<OpenGLFramebuffer>(spec);
        }

        NQ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}