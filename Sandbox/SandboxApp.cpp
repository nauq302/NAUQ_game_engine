

#include <nauq.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <nauq/platform/openGL/OpenGLShader.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string_view>

namespace nq = nauq;

/**
 *
 */
class ExampleLayer :
        public nauq::Layer
{
private:
    nq::Ref<nq::Shader> shader;
    nq::Ref<nq::VertexArray> vertexArray;

    nq::Ref<nq::VertexArray> squareVA;
    nq::Ref<nq::Shader> flatColorShader;
    nq::OrthographicCameraController cameraController;

    nq::Ref<nq::Texture2D> texture, moon;

    nq::ShaderLibrary shaderLibrary;


    glm::vec3 sqColor = { 0.2f, 0.3f, 0.8f };




public:
    ExampleLayer() :
        nq::Layer("Example"),
        cameraController(1024.f / 768.f)
    {
        vertexArray.reset(nq::VertexArray::create());

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        };

        nq::Ref<nq::VertexBuffer> vertexBuffer(nq::VertexBuffer::create(vertices, sizeof(vertices)));

        vertexBuffer->setLayout({
                { nq::ShaderDataType::VEC3F, "a_pos" },
                { nq::ShaderDataType::VEC4F, "a_color" }
        });

        vertexArray->addVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {
                0, 1, 2
        };

        nq::Ref<nq::IndexBuffer> indexBuffer(nq::IndexBuffer::create(indices, 3));
        vertexArray->setIndexBuffer(indexBuffer);

        squareVA.reset(nq::VertexArray::create());

        float sq[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };

        nq::Ref<nq::VertexBuffer> squareVB(nq::VertexBuffer::create(sq, sizeof(sq)));
        squareVB->setLayout({
            { nq::ShaderDataType::VEC3F, "a_pos" },
            { nq::ShaderDataType::VEC2F, "a_textCoord" }
        });
        squareVA->addVertexBuffer(squareVB);

        unsigned int sqi[] = {
                0, 1, 2, 2, 3, 0
        };
        nq::Ref<nq::IndexBuffer> squareIB(nq::IndexBuffer::create(sqi, 6));
        squareVA->setIndexBuffer(squareIB);

        std::string vertexSrc = R"glsl(
            #version 330 core
            #extension GL_ARB_separate_shader_objects: enable

            layout(location = 0) in vec3 a_pos;
            layout(location = 1) in vec4 a_color;

            uniform mat4 u_vp;
            uniform mat4 u_transform;

            out vec3 v_pos;
            out vec4 v_color;

            void main() {
                v_pos = a_pos * 0.5 + 0.5;
                gl_Position = u_vp * u_transform * vec4(a_pos, 1.0);
                v_color = a_color;
            }
        )glsl";

        std::string fragmentSrc = R"glsl(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_pos;
            in vec4 v_color;

            void main() {
                //color = vec4(v_pos, 1.0);
                color = v_color;
            }
        )glsl";


        shader = nq::Shader::create("Vertex pos color", vertexSrc, fragmentSrc);

        std::string vertexFlat = R"glsl(
            #version 330 core
            #extension GL_ARB_separate_shader_objects: enable

            layout(location = 0) in vec3 a_pos;

            uniform mat4 u_vp;
            uniform mat4 u_transform;

            out vec3 v_pos;

            void main() {
                v_pos = a_pos;
                gl_Position = u_vp * u_transform * vec4(a_pos,1.0);
            }
        )glsl";

        std::string fragmentFlat = R"glsl(
            #version 330 core

            uniform vec3 u_color;

            layout(location = 0) out vec4 color;

            in vec3 v_pos;

            void main() {
                color = vec4(u_color,1.0);
            }
        )glsl";

        flatColorShader = nq::Shader::create("Flat Color", vertexFlat, fragmentFlat);

        auto textureShader = shaderLibrary.load("../../Sandbox/shaders/Texture.glsl");

        texture = nq::Texture2D::create("../../Sandbox/res/hv.jpeg");
        moon = nq::Texture2D::create("../../Sandbox/res/moon.png");


        auto t = std::dynamic_pointer_cast<nq::OpenGLShader>(textureShader);
        t->bind();
        t->uploadUniform("u_texture", 0);
    }

public:
    void onUpdate(nq::TimeStep ts) override
    {
        cameraController.onUpdate(ts);

        nq::RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        nq::RenderCommand::clear();

        nq::Renderer::beginScene(cameraController.getCamera());

        static const glm::mat4 eyes(1.0f);
        static glm::mat4 scale = glm::scale(eyes, glm::vec3(0.1f));

//        nq::MaterialRef material = new nq::Material(flatColorShader);
//        material->set("u_color", red);
//        squareMesh->setMaterial(material);

        auto fc = std::dynamic_pointer_cast<nq::OpenGLShader>(flatColorShader);
        fc->bind();
        fc->uploadUniform("u_color", sqColor);

        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20; ++x) {
                glm::vec3 pos(0.11f * x, 0.11f * y, 0.0f);
                glm::mat4 transform = glm::translate(eyes, pos) * scale;
                nq::Renderer::submit(flatColorShader, squareVA, transform);
            }
        }

        auto tr = glm::scale(eyes, glm::vec3(1.5f));

        auto textureShader = shaderLibrary.get("Texture");

        texture->bind();
        nq::Renderer::submit(textureShader, squareVA, tr);

        moon->bind();
        nq::Renderer::submit(textureShader, squareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * tr);

        // Triangle
        //nq::Renderer::submit(shader, vertexArray);

        nq::Renderer::endScene();
    }

    void onEvent(nq::Event& event) override
    {
        cameraController.onEvent(event);
    }

    void onImGuiRender() override
    {
        ImGui::Begin("Setting");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(sqColor));
        ImGui::End();
    }
};

/**
 *
 */
class Sandbox :
        public nauq::Application
{
public:
    explicit Sandbox()
    {
        pushLayer(new ExampleLayer);
    }
    ~Sandbox() override = default;
};


nauq::Application* nauq::createApp()
{
    return new Sandbox;
}