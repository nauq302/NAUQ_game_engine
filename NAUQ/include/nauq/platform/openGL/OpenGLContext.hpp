//
// Created by nauq302 on 06/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_OPENGLCONTEXT_HPP
#define NAUQ_GAME_ENGINE_OPENGLCONTEXT_HPP

#include "nauq/renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace nauq {

    class OpenGLContext :
            public GraphicsContext
    {
    private:
        GLFWwindow* windowHandle;

    public:
        explicit OpenGLContext(GLFWwindow* glfwWindow);

    public:
        void init() override;
        void swapBuffers() override;
    };
}



#endif //NAUQ_GAME_ENGINE_OPENGLCONTEXT_HPP
