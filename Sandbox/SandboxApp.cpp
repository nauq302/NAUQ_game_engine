

#include <nauq.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <nauq/platform/openGL/OpenGLShader.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string_view>

#include <nauq/EntryPoint.hpp>
#include "Sandbox2DLayer.hpp"

namespace nq = nauq;

/**
 *
 */
class Sandbox :
        public nauq::Application
{
public:
    explicit Sandbox()
    {
        pushLayer(new Sandbox2DLayer);
    }
    ~Sandbox() override = default;
};


nauq::Application* nauq::createApp()
{
    return new Sandbox;
}