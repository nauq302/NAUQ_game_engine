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
        uint32_t rendererID = 0;
        std::vector<Ref<VertexBuffer>> vertexBuffers;
        Ref<IndexBuffer> indexBuffer;
    public:
        explicit OpenGLVertexArray();
        ~OpenGLVertexArray() override = default;

    public:
        void bind() override;
        void unbind() override;
        void addVertexBuffer(const Ref<VertexBuffer>& vb) override;
        void setIndexBuffer(const Ref<IndexBuffer>& ib) override;

        [[nodiscard]] const Ref<IndexBuffer>& getIndexBuffer() const override;
    };
}



#endif //NAUQ_GAME_ENGINE_OPENGLVERTEXARRAY_HPP
