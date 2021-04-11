//
// Created by nauq302 on 07/08/2020.
//

#include "nauq/platform/openGL/OpenGLWindow.hpp"

#include "nauq/Log.hpp"
#include "nauq/events/ApplicationEvent.hpp"
#include "nauq/events/KeyEvent.hpp"
#include "nauq/events/MouseEvent.hpp"

#include "nauq/platform/openGL/OpenGLContext.hpp"

namespace nauq {

    /**
     *
     */
    static bool glfw_Initialized = false;

    /**
     *
     * @param error
     * @param description
     */
    static void glfw_errorCallback(int error, const char* description)
    {
        NQ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    /**
     *
     * @param props
     * @return
     */
    Window* Window::create(const WindowProps& props)
    {
        return new OpenGLWindow(props);
    }

    /**
     *
     * @param props
     */
    OpenGLWindow::OpenGLWindow(const nauq::WindowProps& props) :
        window(nullptr)
    {
        init(props);
    }

    /**
     *
     */
    OpenGLWindow::~OpenGLWindow()
    {
        shutdown();
    }

    /**
     *
     * @param props
     */
    void OpenGLWindow::init(const WindowProps& props)
    {
        data.title = props.title;
        data.width = props.width;
        data.height = props.height;

        NQ_CORE_INFO("Create window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!glfw_Initialized) {
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();
            NQ_CORE_ASSERT(success, "Could not initialize GLFW");

            glfwSetErrorCallback(glfw_errorCallback);

            glfw_Initialized = true;
        }

        /// Create a window
        window = glfwCreateWindow(
                static_cast<int>(data.width),
                static_cast<int>(data.height),
                data.title.c_str(),
                nullptr,
                nullptr
        );

        context = new OpenGLContext(window);
        context->init();

        glfwSetWindowUserPointer(window, &data);
        setVSync(true);

        ///-------------------------- Set GLFW callbacks -----------------------------///

        /// Set Window Resize callback
        glfwSetWindowSizeCallback(window, [](GLFWwindow* wd, int width, int height) {
            WindowData& dat = *static_cast<WindowData*>(glfwGetWindowUserPointer(wd));
            dat.width = width;
            dat.height = height;

            WindowResizeEvent event(width, height);
            NQ_CORE_WARN("{0}, {1}", width, height);
            dat.eventCallback(event);
        });

        /// Set Window Close callback
        glfwSetWindowCloseCallback(window, [](GLFWwindow* wd) {
            WindowData& dat = *static_cast<WindowData*>(glfwGetWindowUserPointer(wd));

            WindowCloseEvent event;
            dat.eventCallback(event);
        });

        /// Set Key callback
        glfwSetKeyCallback(window, [](GLFWwindow* wd, int key, int scancode, int action, int mods) {
            WindowData& dat = *static_cast<WindowData*>(glfwGetWindowUserPointer(wd));

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressEvent event(key, 0);
                    dat.eventCallback(event);
                    break;
                }

                case GLFW_REPEAT: {
                    KeyPressEvent event(key, 1);
                    dat.eventCallback(event);
                    break;
                }

                case GLFW_RELEASE: {
                    KeyReleaseEvent event(key);
                    dat.eventCallback(event);
                    break;
                }

                default:;
            }
        });

        /// Set Key Type Callback
        glfwSetCharCallback(window, [](GLFWwindow* wd, unsigned int inputChar) {
            WindowData& dat = *static_cast<WindowData*>(glfwGetWindowUserPointer(wd));

            KeyTypeEvent event(static_cast<int>(inputChar));
            dat.eventCallback(event);
        });

        /// Set Mouse Button Callback
        glfwSetMouseButtonCallback(window, [](GLFWwindow* wd, int button, int action, int mods) {
            WindowData& dat = *static_cast<WindowData*>(glfwGetWindowUserPointer(wd));

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressEvent event(button);
                    dat.eventCallback(event);
                    break;
                }

                case GLFW_RELEASE: {
                    MouseButtonReleaseEvent event(button);
                    dat.eventCallback(event);
                    break;
                }

                default:;
            }
        });

        /// Set Mouse Scroll Callback
        glfwSetScrollCallback(window, [](GLFWwindow* wd, double xOffset, double yOffset) {
            WindowData& dat = *static_cast<WindowData*>(glfwGetWindowUserPointer(wd));

            MouseScrollEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            dat.eventCallback(event);
        });

        /// Set Mouse Move Callback
        glfwSetCursorPosCallback(window, [](GLFWwindow* wd, double xPos, double yPos) {
            WindowData& dat = *static_cast<WindowData*>(glfwGetWindowUserPointer(wd));

            MouseMoveEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
            dat.eventCallback(event);
        });
    }

    /**
     *
     */
    void OpenGLWindow::onUpdate()
    {
        glfwPollEvents();
        context->swapBuffers();
    }

    /**
     *
     * @param enable
     */
    void OpenGLWindow::setVSync(bool enable)
    {
        if (enable) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }

        data.vSync = enable;
    }

    /**
     *
     * @return
     */
    bool OpenGLWindow::isVSync() const
    {
        return data.vSync;
    }

    /**
     *
     */
    void OpenGLWindow::shutdown()
    {
        glfwDestroyWindow(window);
    }

}

