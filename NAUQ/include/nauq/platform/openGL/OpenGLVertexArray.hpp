//
// Created by nauq302 on 02/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_OPENGLVERTEXARRAY_HPP
#define NAUQ_GAME_ENGINE_OPENGLVERTEXARRAY_HPP

#include <nauq/renderer/VertexArray.hpp>

namespace nauq {

    class OpenGLVertexArray :
            public VertexArray
    {
    private:
        std::uint32_t rendererID = 0;
        std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
        std::shared_ptr<IndexBuffer> indexBuffer;
    public:
        explicit OpenGLVertexArray();
        ~OpenGLVertexArray() override = default;

    public:
        void bind() override;
        void unbind() override;
        void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb) override;
        void setIndexBuffer(const std::shared_ptr<IndexBuffer>& ib) override;

        virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override;
    };
}



#endif //NAUQ_GAME_ENGINE_OPENGLVERTEXARRAY_HPP
