//
// Created by nauq302 on 02/12/2020.
//

#include <nauq/platform/openGL/OpenGLVertexArray.hpp>
#include "nauq/renderer/VertexArray.hpp"

#include "nauq/renderer/Renderer.hpp"

namespace nauq {

    Ref<VertexArray> VertexArray::create()
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE: NQ_CORE_ASSERT(false, "RendererAPI::NONE is not currently supported!"); return nullptr;
            case RendererAPI::API::OPEN_GL: return std::make_shared<OpenGLVertexArray>();
        }

        NQ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}