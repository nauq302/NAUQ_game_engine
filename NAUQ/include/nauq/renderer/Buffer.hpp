//
// Created by nauq302 on 14/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_BUFFER_HPP
#define NAUQ_GAME_ENGINE_BUFFER_HPP

#include <cstddef>
#include <cstdint>

namespace nauq {
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

    public:
        static VertexBuffer* create(float* vertices, std::size_t size);

        virtual void bind() const = 0;
        virtual void unbind() const = 0;


    };




    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

    public:
        static IndexBuffer* create(std::uint32_t* indices, std::size_t size);

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        [[nodiscard]] virtual std::size_t getCount() const = 0;

    private:
    };
}




#endif //NAUQ_GAME_ENGINE_BUFFER_HPP
