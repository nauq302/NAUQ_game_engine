//
// Created by nauq302 on 14/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_OPENGLBUFFER_HPP
#define NAUQ_GAME_ENGINE_OPENGLBUFFER_HPP

#include "nauq/renderer/Buffer.hpp"

namespace nauq {

    /**
     *
     */
    class OpenGLVertexBuffer :
            public VertexBuffer
    {
    private:
        uint32_t rendererID = 0;
        BufferLayout layout;

    public:
        explicit OpenGLVertexBuffer(size_t size);
        explicit OpenGLVertexBuffer(float* vertices, size_t size);
        ~OpenGLVertexBuffer() override;

    public:
        void bind() const override;
        void unbind() const override;

        const BufferLayout& getLayout() override { return layout; }
        void setLayout(const BufferLayout& layout) override { this->layout = layout; }
        void setData(const void* data, uint32_t size) override;
    };

    /**
     *
     */
    class OpenGLIndexBuffer :
            public IndexBuffer
    {
    private:
        uint32_t rendererID;
        size_t count;

    public:
        explicit OpenGLIndexBuffer(uint32_t * indices, size_t count);
        ~OpenGLIndexBuffer() override;

    public:
        void bind() const override;
        void unbind() const override;

        size_t getCount() const override;
    };
}



#endif //NAUQ_GAME_ENGINE_OPENGLBUFFER_HPP
