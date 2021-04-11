//
// Created by nauq302 on 09/04/2021.
//

#include "nauq/renderer/Renderer2D.hpp"

#include "nauq/renderer/VertexArray.hpp"
#include "nauq/renderer/Shader.hpp"
#include "nauq/renderer/RenderCommand.hpp"

#include "nauq/platform/openGL/OpenGLShader.hpp"

namespace nauq {

    struct Storage {
        Ref<VertexArray> vertexArray;
        Ref<Shader> shader;
    };

    static Storage* data;

    void Renderer2D::init()
    {
        data = new Storage;

        data->vertexArray = VertexArray::create();

        float sq[] = {
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                 0.5f,  0.5f, 0.0f,
                -0.5f,  0.5f, 0.0f,
        };

        Ref<VertexBuffer> squareVB(VertexBuffer::create(sq, sizeof(sq)));
        squareVB->setLayout({
            { ShaderDataType::VEC3F, "a_pos" },
        });

        data->vertexArray->addVertexBuffer(squareVB);

        unsigned int sqi[] = {
                0, 1, 2, 2, 3, 0
        };
        Ref<IndexBuffer> squareIB = IndexBuffer::create(sqi, 6);
        data->vertexArray->setIndexBuffer(squareIB);

        data->shader = Shader::create("../../Sandbox/shaders/Flat Color.glsl");
    }

    void Renderer2D::shutDown()
    {
        delete data;
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        auto fc = std::dynamic_pointer_cast<OpenGLShader>(data->shader);
        fc->bind();
        fc->uploadUniform("u_vp", camera.getProjection());
        fc->uploadUniform("u_transform", glm::mat4(1.0f));
    }

    void Renderer2D::endScene()
    {

    }

    void Renderer2D::drawQuad(glm::vec2 pos, glm::vec2 size, const glm::vec4& color)
    {
        drawQuad({ pos.x, pos.y, 0.0f }, size, color);
    }

    void Renderer2D::drawQuad(glm::vec3 pos, glm::vec2 size, const glm::vec4& color)
    {
        auto fc = std::dynamic_pointer_cast<OpenGLShader>(data->shader);
        fc->bind();
        fc->uploadUniform("u_color", color);

        data->vertexArray->bind();
        RenderCommand::drawIndexed(data->vertexArray);
    }
}