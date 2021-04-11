//
// Created by nauq302 on 02/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_VERTEXARRAY_HPP
#define NAUQ_GAME_ENGINE_VERTEXARRAY_HPP

#include "Buffer.hpp"

namespace nauq {

    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        [[nodiscard]] virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;

        static Ref<VertexArray> create();
    };
}




#endif //NAUQ_GAME_ENGINE_VERTEXARRAY_HPP
