//
// Created by nauq302 on 02/12/2020.
//

#include "nauq/platform/openGL/OpenGLVertexArray.hpp"


namespace nauq {

    static GLenum ShaderDataTypeToOpenGLDataType(ShaderDataType type)
    {
        switch (type) {
            case ShaderDataType::FLOAT:
            case ShaderDataType::VEC2F:
            case ShaderDataType::VEC3F:
            case ShaderDataType::VEC4F:
            case ShaderDataType::MAT22F:
            case ShaderDataType::MAT33F:
            case ShaderDataType::MAT44F:
                return GL_FLOAT;

            case ShaderDataType::INT:
            case ShaderDataType::VEC2I:
            case ShaderDataType::VEC3I:
            case ShaderDataType::VEC4I:
            case ShaderDataType::MAT22I:
            case ShaderDataType::MAT33I:
            case ShaderDataType::MAT44I:
                return GL_INT;

            case ShaderDataType::BOOL:
                return GL_BOOL;

            default:
                NQ_CORE_ASSERT(false, "Unknown ShaderDataType!");
                return 0;
        }
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &rendererID);
    }

    void OpenGLVertexArray::bind()
    {
        glBindVertexArray(rendererID);
    }

    void OpenGLVertexArray::unbind()
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb)
    {
        glBindVertexArray(rendererID);
        vb->bind();

        NQ_CORE_ASSERT(!vb->getLayout().getElements().empty(), "Vertex Buffer has no layout");

        std::uint32_t index = 0;
        const auto& layout = vb->getLayout();

        for ( const auto& e : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                    index,
                    e.getComponentsCount(),
                    ShaderDataTypeToOpenGLDataType(e.type),
                    e.normalized ? GL_TRUE : GL_FALSE,
                    layout.getStride(),
                    reinterpret_cast<void*>(e.offset)
            );
            ++index;
        }

        vertexBuffers.push_back(vb);
    }

    void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
    {
        glBindVertexArray(rendererID);
        ib->bind();

        indexBuffer = ib;
    }

    const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::getIndexBuffer() const
    {
        return indexBuffer;
    }


}

