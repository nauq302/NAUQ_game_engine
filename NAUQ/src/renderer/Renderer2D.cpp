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

    struct Storage {
        Ref<VertexArray> vertexArray;
        Ref<Shader> textureShader;
        Ref<Texture2D> whiteTexture;
    };

    static Storage* data;

    static glm::mat4 eyes(1.0f);
    static glm::vec4 ones(1.0f);

    void Renderer2D::init()
    {
        NQ_PROFILE_FUNCTION();

        data = new Storage;

        data->vertexArray = VertexArray::create();

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };

        Ref<VertexBuffer> vertexBuffer(VertexBuffer::create(vertices, sizeof(vertices)));
        vertexBuffer->setLayout({
            { ShaderDataType::VEC3F, "a_pos" },
            { ShaderDataType::VEC2F, "a_texCoord" },
        });

        data->vertexArray->addVertexBuffer(vertexBuffer);

        unsigned int indices[] = {
                0, 1, 2, 2, 3, 0
        };
        Ref<IndexBuffer> indexBuffer = IndexBuffer::create(indices, 6);
        data->vertexArray->setIndexBuffer(indexBuffer);

        data->whiteTexture = Texture2D::create(1, 1);
        std::uint32_t whiteData = 0xffffffff;
        data->whiteTexture->setData(&whiteData, sizeof whiteData);

        data->textureShader = Shader::create("../../Sandbox/shaders/Texture.glsl");
        data->textureShader->bind();
        data->textureShader->set("u_texture", 0);
    }

    void Renderer2D::shutDown()
    {
        NQ_PROFILE_FUNCTION();
        delete data;
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        NQ_PROFILE_FUNCTION();
        data->textureShader->bind();
        data->textureShader->set("u_vp", camera.getViewProjection());
    }

    void Renderer2D::endScene()
    {
        NQ_PROFILE_FUNCTION();
    }

    void Renderer2D::drawQuad(glm::vec2 pos, glm::vec2 size, const glm::vec4& color)
    {
        drawQuad({ pos.x, pos.y, 0.0f }, size, color);
    }

    void Renderer2D::drawQuad(glm::vec3 pos, glm::vec2 size, const glm::vec4& color)
    {
        NQ_PROFILE_FUNCTION();

        data->textureShader->set("u_color", color);

        glm::mat transform = glm::translate(eyes, pos) * glm::scale(eyes, { size.x, size.y, 1.0f });

        data->textureShader->set("u_transform", transform);

        data->whiteTexture->bind();

        data->vertexArray->bind();
        RenderCommand::drawIndexed(data->vertexArray);
    }

    void Renderer2D::drawQuad(glm::vec2 pos, glm::vec2 size, const Ref<Texture>& texture,
                               const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
    {
        drawQuad({ pos.x, pos.y, 0.0f }, size, texture,  tintColor);
    }

    void Renderer2D::drawQuad(glm::vec3 pos, glm::vec2 size, const Ref<Texture>& texture,
                               const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
    {
        NQ_PROFILE_FUNCTION();

        glm::mat transform = glm::translate(eyes, pos) * glm::scale(eyes, { size.x, size.y, 1.0f });

        data->textureShader->set("u_color", tintColor);
        data->textureShader->set("u_transform", transform);

        texture->bind();

        data->vertexArray->bind();
        RenderCommand::drawIndexed(data->vertexArray);
        texture->unbind();
    }

    void Renderer2D::drawQuad(glm::vec2 pos, glm::vec2 size, float rotation, const glm::vec4& color)
    {
        drawQuad({ pos.x, pos.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::drawQuad(glm::vec3 pos, glm::vec2 size, float rotation, const glm::vec4& color)
    {
        NQ_PROFILE_FUNCTION();

        data->textureShader->set("u_color", color);

        glm::mat transform = glm::translate(eyes, pos)
                * glm::rotate(eyes, rotation, { 0.0f, 0.0f, 1.0f})
                * glm::scale(eyes, { size.x, size.y, 1.0f });

        data->textureShader->set("u_transform", transform);

        data->whiteTexture->bind();

        data->vertexArray->bind();
        RenderCommand::drawIndexed(data->vertexArray);
    }


    void Renderer2D::drawQuad(glm::vec2 pos, glm::vec2 size, float rotation, const Ref<Texture>& texture,
                                const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
    {
        drawQuad({ pos.x, pos.y, 0.0f }, size, rotation, texture, tintColor);
    }

    void Renderer2D::drawQuad(glm::vec3 pos, glm::vec2 size, float rotation, const Ref<Texture>& texture,
                                const glm::vec4& tintColor /*= glm::vec4(1.0f)*/)
    {
        NQ_PROFILE_FUNCTION();

        glm::mat transform = glm::translate(eyes, pos)
                * glm::rotate(eyes, rotation, { 0.0f, 0.0f, 1.0f})
                * glm::scale(eyes, { size.x, size.y, 1.0f });

        data->textureShader->set("u_color", tintColor);
        data->textureShader->set("u_transform", transform);

        texture->bind();

        data->vertexArray->bind();
        RenderCommand::drawIndexed(data->vertexArray);
        texture->unbind();
    }


}