//
// Created by nauq302 on 14/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_OPENGL_BUFFER_HPP
#define NAUQ_GAME_ENGINE_OPENGL_BUFFER_HPP

#include "nauq/renderer/Buffer.hpp"

namespace nauq {

    /**
     *
     */
    class OpenGLVertexBuffer :
            public VertexBuffer
    {
    private:
        std::uint32_t rendererID;
        BufferLayout layout;

    public:
        explicit OpenGLVertexBuffer(float* vertices, std::size_t size);
        ~OpenGLVertexBuffer() override;

    public:
        void bind() const override;
        void unbind() const override;

        const BufferLayout& getLayout() override { return layout; }
        void setLayout(const BufferLayout& layout) override { this->layout = layout; }

    };

    /**
     *
     */
    class OpenGLIndexBuffer :
            public IndexBuffer
    {
    private:
        std::uint32_t rendererID;
        std::size_t count;

    public:
        explicit OpenGLIndexBuffer(std::uint32_t * indices, std::size_t count);
        ~OpenGLIndexBuffer() override;

    public:
        void bind() const override;
        void unbind() const override;

        virtual size_t getCount() const override;
    };
}



#endif //NAUQ_GAME_ENGINE_OPENGL_BUFFER_HPP
