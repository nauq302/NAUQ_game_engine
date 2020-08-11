//
// Created by nauq302 on 10/08/2020.
//

#include "nauq/imGui/ImGuiLayer.hpp"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "nauq/Application.hpp"

namespace nauq {

    ImGuiLayer::ImGuiLayer() :
        Layer("ImGuiLayer"),
        time(0.0f)
    {

    }

    ImGuiLayer::~ImGuiLayer() = default;

    void ImGuiLayer::onAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = getIO();

        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;

        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach()
    {
    }

    void ImGuiLayer::onUpdate()
    {
        ImGuiIO& io = getIO();

        Application& app = Application::get();
        io.DisplaySize = ImVec2(
                static_cast<float>(app.getWindow().getWidth()),
                static_cast<float>(app.getWindow().getHeight())
        );

        auto current = static_cast<float>(glfwGetTime());
        io.DeltaTime = time > 0.0f ? (current - time) : (1.0f / 60.0f);
        time = current;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();


        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowResizeEvent>(NAUQ_BIND_EVENT_FN(ImGuiLayer::onWindowResize));
        dispatcher.dispatch<MouseButtonPressEvent>(NAUQ_BIND_EVENT_FN(ImGuiLayer::onMouseButtonPress));
        dispatcher.dispatch<MouseButtonReleaseEvent>(NAUQ_BIND_EVENT_FN(ImGuiLayer::onMouseButtonRelease));
        dispatcher.dispatch<MouseMoveEvent>(NAUQ_BIND_EVENT_FN(ImGuiLayer::onMouseMove));
        dispatcher.dispatch<MouseScrollEvent>(NAUQ_BIND_EVENT_FN(ImGuiLayer::onMouseScroll));
        dispatcher.dispatch<KeyPressEvent>(NAUQ_BIND_EVENT_FN(ImGuiLayer::onKeyPress));
        dispatcher.dispatch<KeyReleaseEvent>(NAUQ_BIND_EVENT_FN(ImGuiLayer::onKeyRelease));
        dispatcher.dispatch<KeyTypeEvent>(NAUQ_BIND_EVENT_FN(ImGuiLayer::onKeyType));

    }

    bool ImGuiLayer::onMouseButtonPress(MouseButtonPressEvent& event)
    {
        getIO().MouseDown[event.getMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::onMouseButtonRelease(MouseButtonReleaseEvent& event)
    {
        getIO().MouseDown[event.getMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::onMouseMove(MouseMoveEvent& event)
    {
        getIO().MousePos = ImVec2(event.getX(), event.getY());
        return false;
    }

    bool ImGuiLayer::onMouseScroll(MouseScrollEvent& event)
    {
        ImGuiIO& io = getIO();

        io.MouseWheelH += event.getXOffset();
        io.MouseWheel += event.getYOffset();

        return false;
    }

    bool ImGuiLayer::onKeyPress(KeyPressEvent& event)
    {
        ImGuiIO& io = getIO();

        io.KeysDown[event.getKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::onKeyRelease(KeyReleaseEvent& event)
    {
        ImGuiIO& io = getIO();

        io.KeysDown[event.getKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::onKeyType(KeyTypeEvent& event)
    {
        int keycode = event.getKeyCode();

        if (keycode > 0 && keycode < 0x10000) {
            getIO().AddInputCharacter(static_cast<unsigned short>(keycode));
        }

        return false;
    }

    bool ImGuiLayer::onWindowResize(WindowResizeEvent& event)
    {
        ImGuiIO& io = getIO();

        io.DisplaySize = ImVec2(static_cast<float>(event.getWidth()), static_cast<float>(event.getHeight()));
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, event.getWidth(), event.getHeight());

        return false;
    }


}