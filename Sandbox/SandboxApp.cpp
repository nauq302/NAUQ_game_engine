

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
    nq::Ref<nq::Shader> flatColorShader, textureShader;
    nq::OrthographicCamera camera;

    nq::Ref<nq::Texture2D> texture, moon;

    glm::vec3 camPos;
    float camSpeed = 0.5f;

    float camRot = 0.0f;
    float camRotSpeed = 180.0f;

    glm::vec3 sqColor = { 0.2f, 0.3f, 0.8f };




public:
    ExampleLayer() :
        nq::Layer("Example"),
        camera(-2.0f, 2.0f, -1.5f, 1.5f),
        camPos(0.0f),
        camRot(0.0f)
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

        shader.reset(nq::Shader::create(vertexSrc, fragmentSrc));

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

        flatColorShader.reset(nq::Shader::create(vertexFlat, fragmentFlat));

        std::string vertexTexture = R"glsl(
            #version 330 core
            #extension GL_ARB_separate_shader_objects: enable

            layout(location = 0) in vec3 a_pos;
            layout(location = 1) in vec2 a_texCoord;

            uniform mat4 u_vp;
            uniform mat4 u_transform;

            out vec2 v_texCoord;

            void main() {
                v_texCoord = a_texCoord;
                gl_Position = u_vp * u_transform * vec4(a_pos,1.0);
            }
        )glsl";

        std::string fragmentTexture = R"glsl(
            #version 330 core

            uniform vec3 u_color;
            uniform sampler2D u_texture;

            layout(location = 0) out vec4 color;

            in vec2 v_texCoord;

            void main() {
                color = texture(u_texture, v_texCoord);
            }
        )glsl";

        textureShader.reset(nq::Shader::create(vertexTexture, fragmentTexture));


        texture = nq::Texture2D::create("../../Sandbox/res/hv.jpeg");
        moon = nq::Texture2D::create("../../Sandbox/res/moon.png");


        auto t = std::dynamic_pointer_cast<nq::OpenGLShader>(textureShader);
        t->bind();
        t->uploadUniform("u_texture", 0);
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

        texture->bind();
        nq::Renderer::submit(textureShader, squareVA, tr);

        moon->bind();
        nq::Renderer::submit(textureShader, squareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * tr);

        // Triangle
        //nq::Renderer::submit(shader, vertexArray);

        nq::Renderer::endScene();


    }

    void onEvent(nauq::Event& event) override
    {

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