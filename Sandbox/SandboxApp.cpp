

#include <nauq.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace nq = nauq;

/**
 *
 */
class ExampleLayer :
        public nauq::Layer
{
private:
    std::shared_ptr<nq::Shader> shader;
    std::shared_ptr<nq::VertexArray> vertexArray;

    std::shared_ptr<nq::VertexArray> squareVA;
    std::shared_ptr<nq::Shader> blueShader;
    nq::OrthographicCamera camera;

    glm::vec3 camPos;
    float camSpeed = 0.5f;

    float camRot = 0.0f;
    float camRotSpeed = 180.0f;

    glm::vec3 sqPos;
    float sqSpeed = 0.5f;


public:
    ExampleLayer() :
        nq::Layer("Example"),
        camera(-2.0f, 2.0f, -1.5f, 1.5f),
        camPos(0.0f),
        camRot(0.0f),
        sqPos(0.0f)
    {
        vertexArray.reset(nq::VertexArray::create());

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        };

        std::shared_ptr<nq::VertexBuffer> vertexBuffer(nq::VertexBuffer::create(vertices, sizeof(vertices)));

        vertexBuffer->setLayout({
                { nq::ShaderDataType::VEC3F, "a_pos" },
                { nq::ShaderDataType::VEC4F, "a_color" }
        });

        vertexArray->addVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {
                0, 1, 2
        };

        std::shared_ptr<nq::IndexBuffer> indexBuffer(nq::IndexBuffer::create(indices, 3));
        vertexArray->setIndexBuffer(indexBuffer);

        squareVA.reset(nq::VertexArray::create());

        float sq[] = {
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                 0.5f,  0.5f, 0.0f,
                -0.5f,  0.5f, 0.0f,
        };

        std::shared_ptr<nq::VertexBuffer> squareVB(nq::VertexBuffer::create(sq, sizeof(sq)));
        squareVB->setLayout({
            { nq::ShaderDataType::VEC3F, "a_pos" }
        });
        squareVA->addVertexBuffer(squareVB);

        unsigned int sqi[] = {
                0, 1, 2, 2, 3, 0
        };
        std::shared_ptr<nq::IndexBuffer> squareIB(nq::IndexBuffer::create(sqi, 6));
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

        std::string vertexBlue = R"glsl(
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

        std::string fragmentBlue = R"glsl(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_pos;

            void main() {
                color = vec4(0.2,0.3,0.8,1.0);
            }
        )glsl";

        shader = std::make_unique<nq::Shader>(vertexSrc, fragmentSrc);
        blueShader = std::make_unique<nq::Shader>(vertexBlue, fragmentBlue);
    }

public:
    void onUpdate(nq::TimeStep ts) override
    {
        if (nq::Input::isKeyPress(NQ_KEY_LEFT))
            camPos.x -= camSpeed * ts;

        else if (nq::Input::isKeyPress(NQ_KEY_RIGHT))
            camPos.x += camSpeed * ts;

        else if (nq::Input::isKeyPress(NQ_KEY_DOWN))
            camPos.y -= camSpeed * ts;

        else if (nq::Input::isKeyPress(NQ_KEY_UP))
            camPos.y += camSpeed * ts;

        if (nq::Input::isKeyPress(NQ_KEY_A))
            camRot += camRotSpeed * ts;

        if (nq::Input::isKeyPress(NQ_KEY_D))
            camRot -= camRotSpeed * ts;

        nq::RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        nq::RenderCommand::clear();

        camera.setPosition(camPos);
        camera.setRotation(camRot);

        nq::Renderer::beginScene(camera);

        static const glm::mat4 eyes(1.0f);
        static glm::mat4 scale = glm::scale(eyes, glm::vec3(0.1f));

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                glm::vec3 pos(0.11f * i, 0.11f * j, 0.0f);
                glm::mat4 transform = glm::translate(eyes, pos) * scale;
                nq::Renderer::submit(blueShader, squareVA, transform);
            }
        }

        nq::Renderer::submit(shader, vertexArray);

        nq::Renderer::endScene();


    }

    void onEvent(nauq::Event& event) override
    {

    }

    void onImGuiRender() override
    {
    }
};

/**
 *you
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