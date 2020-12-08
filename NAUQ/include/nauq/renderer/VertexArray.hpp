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

        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        [[nodiscard]] virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;

        static VertexArray* create();
    };
}




#endif //NAUQ_GAME_ENGINE_VERTEXARRAY_HPP
