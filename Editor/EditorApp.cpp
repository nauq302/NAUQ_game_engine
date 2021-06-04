

#include <nauq.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <nauq/platform/openGL/OpenGLShader.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string_view>

#include <nauq/core/EntryPoint.hpp>
#include "Editor2DLayer.hpp"

namespace nauq {

    /**
     *
     */
    class Editor :
            public Application
    {
    public:
        explicit Editor()
        {
            pushLayer(new Editor2DLayer);
        }

        ~Editor() override = default;
    };


    Application* createApp()
    {
        return new Editor;
    }

}