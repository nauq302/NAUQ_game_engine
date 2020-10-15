//
// Created by nauq302 on 14/10/2020.
//

#include "nauq/platform/openGL/OpenGL_Buffer.hpp"

namespace nauq {

    nauq::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, std::size_t size)
    {
        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }


    void nauq::OpenGLVertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    }

    void nauq::OpenGLVertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

///////////////////////////////////////////////////////////////////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(std::uint32_t* vertices, std::size_t count) :
        count(count)
    {
        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(std::uint32_t), vertices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLIndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
    }

    void OpenGLIndexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    std::size_t OpenGLIndexBuffer::getCount() const
    {
        return count;
    }
}