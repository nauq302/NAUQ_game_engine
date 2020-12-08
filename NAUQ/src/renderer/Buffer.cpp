//
// Created by nauq302 on 14/10/2020.
//

#include "nauq/Log.hpp"
#include "nauq/renderer/Buffer.hpp"
#include "nauq/renderer/Renderer.hpp"

#include "nauq/platform/openGL/OpenGL_Buffer.hpp"

namespace nauq {

    /**
     *
     * @param vertices
     * @param size
     * @return
     */
    VertexBuffer* VertexBuffer::create(float* vertices, std::size_t size)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE:
                NAUQ_CORE_ASSERT(false, "RendererAPI::NONE is not current supported!");

            case RendererAPI::API::OPEN_GL:
                return new OpenGLVertexBuffer(vertices, size);

            default:
                return nullptr;
        }

        NAUQ_CORE_ASSERT(false, "Unknown RendererAPI!");
    }

    /**
     *
     * @param indices
     * @param size
     * @return
     */
    IndexBuffer* IndexBuffer::create(std::uint32_t* indices, std::size_t size)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE:
                NAUQ_CORE_ASSERT(false, "RendererAPI::NONE is not current supported!");

            case RendererAPI::API::OPEN_GL:
                return new OpenGLIndexBuffer(indices, size);

            default:
                return nullptr;
        }

        NAUQ_CORE_ASSERT(false, "Unknown RendererAPI!");
    }
}