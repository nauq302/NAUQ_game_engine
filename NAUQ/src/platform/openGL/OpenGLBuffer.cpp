//
// Created by nauq302 on 14/10/2020.
//

#include "nauq/platform/openGL/OpenGLBuffer.hpp"

#include "nauq/debug/Instrumentor.hpp"

namespace nauq {

    OpenGLVertexBuffer::OpenGLVertexBuffer(std::size_t size)
    {
        NQ_PROFILE_FUNCTION();

        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    nauq::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, std::size_t size)
    {
        NQ_PROFILE_FUNCTION();

        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        NQ_PROFILE_FUNCTION();

        glDeleteBuffers(1, &rendererID);
    }

    void nauq::OpenGLVertexBuffer::bind() const
    {
        NQ_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    }

    void nauq::OpenGLVertexBuffer::unbind() const
    {
        NQ_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::setData(const void* data, std::uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }



///////////////////////////////////////////////////////////////////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(std::uint32_t* vertices, std::size_t count) :
        count(count)
    {
        NQ_PROFILE_FUNCTION();

        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(std::uint32_t), vertices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        NQ_PROFILE_FUNCTION();

        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLIndexBuffer::bind() const
    {
        NQ_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
    }

    void OpenGLIndexBuffer::unbind() const
    {
        NQ_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    std::size_t OpenGLIndexBuffer::getCount() const
    {
        return count;
    }
}