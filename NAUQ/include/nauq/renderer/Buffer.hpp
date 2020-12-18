//
// Created by nauq302 on 14/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_BUFFER_HPP
#define NAUQ_GAME_ENGINE_BUFFER_HPP

#include "nauq/Log.hpp"
#include <cstddef>
#include <cstdint>
#include <utility>

namespace nauq {


    enum class ShaderDataType
    {
        NONE = 0,
        FLOAT, VEC2F, VEC3F, VEC4F, MAT22F, MAT33F, MAT44F,
        INT, VEC2I, VEC3I, VEC4I, MAT22I, MAT33I, MAT44I,
        BOOL
    };

    constexpr std::uint32_t shaderDataTypeSize(ShaderDataType type)
    {
        switch (type) {
            case ShaderDataType::FLOAT: return sizeof(float);
            case ShaderDataType::VEC2F: return sizeof(float) * 2;
            case ShaderDataType::VEC3F: return sizeof(float) * 3;
            case ShaderDataType::VEC4F: return sizeof(float) * 4;
            case ShaderDataType::MAT22F: return sizeof(float) * 2 * 2;
            case ShaderDataType::MAT33F: return sizeof(float) * 3 * 3;
            case ShaderDataType::MAT44F: return sizeof(float) * 4 * 4;

            case ShaderDataType::INT: return sizeof(int);
            case ShaderDataType::VEC2I: return sizeof(int) * 2;
            case ShaderDataType::VEC3I: return sizeof(int) * 3;
            case ShaderDataType::VEC4I: return sizeof(int) * 4;
            case ShaderDataType::MAT22I: return sizeof(int) * 2 * 2;
            case ShaderDataType::MAT33I: return sizeof(int) * 3 * 3;
            case ShaderDataType::MAT44I: return sizeof(int) * 4 * 4;

            case ShaderDataType::BOOL: return sizeof(bool);

            default:
                NQ_CORE_ASSERT(false, "Unknown ShaderDataType!");
                return 0;
        }
    }

    /**
     *
     */
    struct BufferElement
    {
        std::string name;
        ShaderDataType type;
        std::uint32_t offset;
        std::uint32_t size;
        bool normalized;

        BufferElement(ShaderDataType type, std::string name, bool normalized = false) :
            name(std::move(name)), type(type), size(shaderDataTypeSize(type)), offset(0), normalized(normalized) {}

        [[nodiscard]] std::uint32_t getComponentsCount() const
        {
            switch (type) {
                case ShaderDataType::FLOAT: return 1;
                case ShaderDataType::VEC2F: return 2;
                case ShaderDataType::VEC3F: return 3;
                case ShaderDataType::VEC4F: return 4;
                case ShaderDataType::MAT22F: return 2 * 2;
                case ShaderDataType::MAT33F: return 3 * 3;
                case ShaderDataType::MAT44F: return 4 * 4;

                case ShaderDataType::INT: return 1;
                case ShaderDataType::VEC2I: return 2;
                case ShaderDataType::VEC3I: return 3;
                case ShaderDataType::VEC4I: return 4;
                case ShaderDataType::MAT22I: return 2 * 2;
                case ShaderDataType::MAT33I: return 3 * 3;
                case ShaderDataType::MAT44I: return 4 * 4;

                case ShaderDataType::BOOL: return 1;

                default:
                    NQ_CORE_ASSERT(false, "Unknown ShaderDataType!");
                    return 0;
            }
        }
    };

    /**
     *
     */
    class BufferLayout
    {
    private:
        std::vector<BufferElement> elements;
        std::uint32_t stride = 0;

    public:

        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements) : elements(elements)
        {
            calculateOffsetAndStride();
        }

    public:
        [[nodiscard]] inline const std::vector<BufferElement>& getElements() const { return elements; }
        [[nodiscard]] inline std::uint32_t getStride() const { return stride; }

        inline std::vector<BufferElement>::iterator begin() { return elements.begin(); }
        inline std::vector<BufferElement>::iterator end() { return elements.end(); }
        [[nodiscard]] inline std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
        [[nodiscard]] inline std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

    private:
        void calculateOffsetAndStride()
        {
            for (auto& e : elements) {
                e.offset = stride;
                stride += e.size;
            }
        }

    };


    /**
     *
     */
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

    public:
        static VertexBuffer* create(float* vertices, std::size_t size);

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual const BufferLayout& getLayout() = 0;
        virtual void setLayout(const BufferLayout& layout) = 0;
    };

    /**
     *
     */
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
