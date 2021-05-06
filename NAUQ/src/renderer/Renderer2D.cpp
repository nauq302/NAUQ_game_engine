//
// Created by nauq302 on 09/04/2021.
//

#include "nauq/renderer/Renderer2D.hpp"

#include "nauq/renderer/VertexArray.hpp"
#include "nauq/renderer/Shader.hpp"
#include "nauq/renderer/RenderCommand.hpp"
#include "nauq/debug/Instrumentor.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace nauq {

    extern const char* vs;
    extern const char* fs;

    void setData(const glm::mat4& transform, const glm::vec4& color, const std::array<glm::vec2,4>& texCoords, float textureIndex, float tilingFactor = 1.0f);

    constexpr std::array<glm::vec2,4> whole = { glm::vec2{ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

    struct QuadVertex {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoord;
        float textIndex;
        float tilingFactor;
        /// TO DO: texId, maskId
    };

    struct Data {
        static constexpr std::uint32_t maxQuads = 1024;
        static constexpr std::uint32_t maxVertices = maxQuads * 4;
        static constexpr std::uint32_t maxIndices = maxQuads * 6;

        static constexpr std::uint32_t maxTextureSlots = 32;
        static constexpr glm::vec4 quadVertexPositions[4] = {
                { -0.5f, -0.5f, 0.0f, 1.0f },
                {  0.5f, -0.5f, 0.0f, 1.0f },
                {  0.5f,  0.5f, 0.0f, 1.0f },
                { -0.5f,  0.5f, 0.0f, 1.0f },
        };

        Ref<VertexArray> vertexArray;
        Ref<Shader> textureShader;
        Ref<VertexBuffer> quadVertexBuffer;
        Ref<Texture2D> whiteTexture;

        std::uint32_t quadIndexCount = 0;
        QuadVertex* quadVertexBufferBase = nullptr;
        QuadVertex* quadVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>, maxTextureSlots> texSlots = { nullptr, };
        std::uint32_t texSlotIndex = 1; /// 0 - white texture

        Renderer2D::Statistics stats;
    };

    static Data* data;

    /**
     *
     */
    void Renderer2D::init()
    {
        NQ_PROFILE_FUNCTION();
        data = new Data;

        data->vertexArray = VertexArray::create();

        data->quadVertexBuffer = VertexBuffer::create(Data::maxVertices * sizeof(QuadVertex));
        data->quadVertexBuffer->setLayout({
            { ShaderDataType::VEC3F, "a_pos" },
            { ShaderDataType::VEC4F, "a_color" },
            { ShaderDataType::VEC2F, "a_texCoord" },
            { ShaderDataType::FLOAT, "a_texIndex" },
            { ShaderDataType::FLOAT, "a_tilingFactor" },
        });
        data->vertexArray->addVertexBuffer(data->quadVertexBuffer);

        data->quadVertexBufferBase = new QuadVertex[Data::maxVertices];

        auto* quadIndices = new std::uint32_t[Data::maxIndices];

        std::uint32_t offset = 0;
        for (std::uint32_t i = 0; i < Data::maxIndices; i += 6) {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;
            quadIndices[i + 3] = offset + 0;
            quadIndices[i + 4] = offset + 2;
            quadIndices[i + 5] = offset + 3;

            offset += 4;
        }

        Ref<IndexBuffer> indexBuffer = IndexBuffer::create(quadIndices, Data::maxIndices);
        data->vertexArray->setIndexBuffer(indexBuffer);
        delete[] quadIndices;

        data->whiteTexture = Texture2D::create(1, 1);
        std::uint32_t whiteData = 0xffffffff;
        data->whiteTexture->setData(&whiteData, sizeof whiteData);

        //data->textureShader = Shader::create("../../Sandbox/shaders/Texture.glsl");

        int samplers[Data::maxTextureSlots];
        for (int i = 0; i < Data::maxTextureSlots; ++i) {
            samplers[i] = i;
        }

        data->textureShader = Shader::create("Texture", vs, fs);

        data->textureShader->bind();
        data->textureShader->set("u_textures", samplers);

        data->texSlots[0] = data->whiteTexture;
    }

    /**
     *
     */
    void Renderer2D::shutDown()
    {
        NQ_PROFILE_FUNCTION();
        delete[] data->quadVertexBufferBase;
        delete data;
    }

    /**
     *
     * @param camera
     */
    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        NQ_PROFILE_FUNCTION();
        data->textureShader->bind();
        data->textureShader->set("u_vp", camera.getViewProjection());

        data->quadIndexCount = 0;
        data->quadVertexBufferPtr = data->quadVertexBufferBase;

        data->texSlotIndex = 1;
    }

    /**
     *
     */
    void Renderer2D::endScene()
    {
        NQ_PROFILE_FUNCTION();

        std::uint32_t dataSize = (data->quadVertexBufferPtr - data->quadVertexBufferBase) * sizeof(QuadVertex);
        data->quadVertexBuffer->setData(data->quadVertexBufferBase, dataSize);

        flush();
    }

    /**
     *
     */
    void Renderer2D::flush()
    {
        if (data->quadIndexCount == 0) {
            return; /// Nothing to draw
        }

        for (std::uint32_t i = 0; i < data->texSlotIndex; ++i) {
            data->texSlots[i]->bind(i);
        }
        RenderCommand::drawIndexed(data->vertexArray, data->quadIndexCount);

        ++data->stats.drawCalls;
    }

    /**
     *
     */
    void Renderer2D::flushAndReset()
    {
        endScene();

        data->quadIndexCount = 0;
        data->quadVertexBufferPtr = data->quadVertexBufferBase;

        data->texSlotIndex = 1;
    }

    /**
     *
     * @param pos
     * @param size
     * @param color
     */
    void Renderer2D::drawQuad(glm::vec2 pos, glm::vec2 size, const glm::vec4& color)
    {
        drawQuad({ pos.x, pos.y, 0.0f }, size, color);
    }

    /**
     *
     * @param pos
     * @param size
     * @param color
     */
    void Renderer2D::drawQuad(glm::vec3 pos, glm::vec2 size, const glm::vec4& color)
    {
        NQ_PROFILE_FUNCTION();

        if (data->quadIndexCount >= Data::maxIndices) {
            flushAndReset();
        }

        glm::mat4 transform = glm::translate(eyes, pos) * glm::scale(eyes, { size.x, size.y, 1.0f });

        setData(transform, color, whole, 0.0f);
    }

    /**
     *
     * @param pos
     * @param size
     * @param texture
     * @param tilingFactor
     * @param tintColor
     */
    void Renderer2D::drawQuad(glm::vec2 pos, glm::vec2 size, const Ref<Texture2D>& texture,
                              float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= white*/)
    {
        drawQuad({ pos.x, pos.y, 0.0f }, size, texture, tilingFactor, tintColor);
    }

    /**
     *
     * @param pos
     * @param size
     * @param texture
     * @param tilingFactor
     * @param tintColor
     */
    void Renderer2D::drawQuad(glm::vec3 pos, glm::vec2 size, const Ref<Texture2D>& texture,
                              float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= white*/)
    {
        NQ_PROFILE_FUNCTION();

        if (data->quadIndexCount >= Data::maxIndices) {
            flushAndReset();
        }

        float textureIndex = 0.0f;

        for (std::uint32_t i = 1; i < data->texSlotIndex; ++i) {
            if (*data->texSlots[i] == *texture) {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        if (textureIndex == 0.0f) {
            textureIndex = static_cast<float>(data->texSlotIndex);
            data->texSlots[data->texSlotIndex] = texture;
            ++data->texSlotIndex;
        }

        glm::mat4 transform = glm::translate(eyes, pos) * glm::scale(eyes, { size.x, size.y, 1.0f });

        setData(transform, tintColor, whole, textureIndex, tilingFactor);
    }

    /**
     *
     * @param pos
     * @param size
     * @param radians
     * @param color
     */
    void Renderer2D::drawRotatedQuad(glm::vec2 pos, glm::vec2 size, float radians, const glm::vec4& color)
    {
        drawRotatedQuad({ pos.x, pos.y, 0.0f }, size, radians, color);
    }

    /**
     *
     * @param pos
     * @param size
     * @param radians
     * @param color
     */
    void Renderer2D::drawRotatedQuad(glm::vec3 pos, glm::vec2 size, float radians, const glm::vec4& color)
    {
        NQ_PROFILE_FUNCTION();

        if (data->quadIndexCount >= Data::maxIndices) {
            flushAndReset();
        }

        glm::mat4 transform = glm::translate(eyes, pos)
                * glm::rotate(eyes, radians, { 0.0f, 0.0f, 1.0f})
                * glm::scale(eyes, { size.x, size.y, 1.0f });

        setData(transform, color, whole, 0.0f);
    }

    /**
     *
     * @param pos
     * @param size
     * @param radians
     * @param texture
     * @param tilingFactor
     * @param tintColor
     */
    void Renderer2D::drawRotatedQuad(glm::vec2 pos, glm::vec2 size, float radians, const Ref<Texture2D>& texture,
                                     float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= white*/)
    {
        drawRotatedQuad({ pos.x, pos.y, 0.0f }, size, radians, texture, tilingFactor, tintColor);
    }

    /**
     *
     * @param pos
     * @param size
     * @param radians
     * @param texture
     * @param tilingFactor
     * @param tintColor
     */
    void Renderer2D::drawRotatedQuad(glm::vec3 pos, glm::vec2 size, float radians, const Ref<Texture2D>& texture,
                                     float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= white*/)
    {
        NQ_PROFILE_FUNCTION();

        if (data->quadIndexCount >= Data::maxIndices) {
            flushAndReset();
        }

        float textureIndex = 0.0f;

        for (std::uint32_t i = 1; i < data->texSlotIndex; ++i) {
            if (*data->texSlots[i] == *texture) {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        if (textureIndex == 0.0f) {
            textureIndex = static_cast<float>(data->texSlotIndex);
            data->texSlots[data->texSlotIndex] = texture;
            ++data->texSlotIndex;
        }

        glm::mat4 transform = glm::translate(eyes, pos)
                  * glm::rotate(eyes, radians, { 0.0f, 0.0f, 1.0f })
                  * glm::scale(eyes, { size.x, size.y, 1.0f });

        setData(transform, tintColor, whole, textureIndex, tilingFactor);
    }

    /**
     *
     * @param pos
     * @param size
     * @param texture
     * @param tilingFactor
     * @param tintColor
     */
    void Renderer2D::drawQuad(glm::vec2 pos, glm::vec2 size, const Ref<SubTexture2D>& subTexture,
                              float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= white*/)
    {
        drawQuad({ pos.x, pos.y, 0.0f }, size, subTexture, tilingFactor, tintColor);
    }

    /**
     *
     * @param pos
     * @param size
     * @param texture
     * @param tilingFactor
     * @param tintColor
     */
    void Renderer2D::drawQuad(glm::vec3 pos, glm::vec2 size, const Ref<SubTexture2D>& subTexture,
                              float tilingFactor /*= 1.0f*/, const glm::vec4& tintColor /*= white*/)
    {
        NQ_PROFILE_FUNCTION();

        if (data->quadIndexCount >= Data::maxIndices) {
            flushAndReset();
        }

        float textureIndex = 0.0f;

        for (std::uint32_t i = 1; i < data->texSlotIndex; ++i) {
            if (*data->texSlots[i] == *subTexture->getTexture()) {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        if (textureIndex == 0.0f) {
            textureIndex = static_cast<float>(data->texSlotIndex);
            data->texSlots[data->texSlotIndex] = subTexture->getTexture();
            ++data->texSlotIndex;
        }

        glm::mat4 transform = glm::translate(eyes, pos) * glm::scale(eyes, { size.x, size.y, 1.0f });

        setData(transform, tintColor, subTexture->getCoords(), textureIndex, tilingFactor);
    }

    const char* vs = R"vs(
        #version 330 core
        #extension GL_ARB_separate_shader_objects: enable

        layout(location = 0) in vec3 a_pos;
        layout(location = 1) in vec4 a_color;
        layout(location = 2) in vec2 a_texCoord;
        layout(location = 3) in float a_texIndex;
        layout(location = 4) in float a_tilingFactor;

        uniform mat4 u_vp;

        out vec4 v_color;
        out vec2 v_texCoord;
        out float v_texIndex;
        out float v_tilingFactor;

        void main() {
            v_color = a_color;
            v_texCoord = a_texCoord;
            v_texIndex = a_texIndex;
            v_tilingFactor = a_tilingFactor;
            gl_Position = u_vp * vec4(a_pos, 1.0);
        }
    )vs";

    const char* fs = R"fs(
        #version 330 core

        uniform vec4 u_color;
        uniform sampler2D u_textures[32];
        uniform float u_tilingFactor;

        layout(location = 0) out vec4 color;

        in vec4 v_color;
        in vec2 v_texCoord;
        in float v_texIndex;
        in float v_tilingFactor;

        void main() {
            color = texture(u_textures[int(v_texIndex)], v_texCoord * v_tilingFactor) * v_color;
//            color = v_color;
        }
    )fs";

    void setData(const glm::mat4& transform, const glm::vec4& color, const std::array<glm::vec2,4>& texCoords, float textureIndex, float tilingFactor)
    {
        data->quadVertexBufferPtr->position = transform * Data::quadVertexPositions[0];
        data->quadVertexBufferPtr->color = color;
        data->quadVertexBufferPtr->texCoord = texCoords[0];
        data->quadVertexBufferPtr->textIndex = textureIndex;
        data->quadVertexBufferPtr->tilingFactor = tilingFactor;
        ++data->quadVertexBufferPtr;

        data->quadVertexBufferPtr->position = transform * Data::quadVertexPositions[1];
        data->quadVertexBufferPtr->color = color;
        data->quadVertexBufferPtr->texCoord = texCoords[1];
        data->quadVertexBufferPtr->textIndex = textureIndex;
        data->quadVertexBufferPtr->tilingFactor = tilingFactor;
        ++data->quadVertexBufferPtr;

        data->quadVertexBufferPtr->position = transform * Data::quadVertexPositions[2];
        data->quadVertexBufferPtr->color = color;
        data->quadVertexBufferPtr->texCoord = texCoords[2];
        data->quadVertexBufferPtr->textIndex = textureIndex;
        data->quadVertexBufferPtr->tilingFactor = tilingFactor;
        ++data->quadVertexBufferPtr;

        data->quadVertexBufferPtr->position = transform * Data::quadVertexPositions[3];
        data->quadVertexBufferPtr->color = color;
        data->quadVertexBufferPtr->texCoord = texCoords[3];
        data->quadVertexBufferPtr->textIndex = textureIndex;
        data->quadVertexBufferPtr->tilingFactor = tilingFactor;
        ++data->quadVertexBufferPtr;

        data->quadIndexCount += 6;

        ++data->stats.quadCount;
    }

    void Renderer2D::resetStats()
    {
        data->stats = { 0, 0 };
    }

    Renderer2D::Statistics Renderer2D::getStats()
    {
        return data->stats;
    }


}

