//
// Created by nauq302 on 14/10/2020.
//

#include "nauq/Log.hpp"
#include "nauq/renderer/Buffer.hpp"
#include "nauq/renderer/Renderer.hpp"

#include "nauq/platform/openGL/OpenGLBuffer.hpp"

namespace nauq {

    template <typename... Ts>
    Ref<VertexBuffer> createVB(Ts&&... ts)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE:
                NQ_CORE_ASSERT(false, "RendererAPI::NONE is not current supported!");

            case RendererAPI::API::OPEN_GL:
                return createRef<OpenGLVertexBuffer>(std::forward<Ts>(ts)...);

            default:
                return nullptr;
        }

        NQ_CORE_ASSERT(false, "Unknown RendererAPI!");
    }


    /**
     *
     * @param vertices
     * @param size
     * @return
     */
    Ref<VertexBuffer> VertexBuffer::create(float* vertices, size_t size)
    {
        return createVB(vertices, size);
    }

    Ref<VertexBuffer> VertexBuffer::create(size_t size)
    {
        return createVB(size);
    }

    /**
     *
     * @param indices
     * @param size
     * @return
     */
    Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, size_t count)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE:
                NQ_CORE_ASSERT(false, "RendererAPI::NONE is not current supported!");

            case RendererAPI::API::OPEN_GL:
                return std::make_shared<OpenGLIndexBuffer>(indices, count);

            default:
                return nullptr;
        }

        NQ_CORE_ASSERT(false, "Unknown RendererAPI!");
    }
}