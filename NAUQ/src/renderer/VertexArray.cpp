//
// Created by nauq302 on 02/12/2020.
//

#include <nauq/platform/openGL/OpenGLVertexArray.hpp>
#include "nauq/renderer/VertexArray.hpp"

#include "nauq/renderer/Renderer.hpp"

namespace nauq {

    VertexArray* VertexArray::create()
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE: NAUQ_CORE_ASSERT(false, "RendererAPI::NONE is not currently supported!"); return nullptr;
            case RendererAPI::API::OPEN_GL: return new OpenGLVertexArray;
        }

        NAUQ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}