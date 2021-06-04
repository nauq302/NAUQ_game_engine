//
// Created by nauq302 on 10/08/2020.
//

#include "nauq/imGui/ImGuiLayer.hpp"

#include "imgui.h"

#include "nauq/imGui/ImGuiImpl.hpp"
#include "nauq/core/Application.hpp"
#include "nauq/debug/Instrumentor.hpp"

namespace nauq {

    ImGuiLayer::ImGuiLayer() :
        Layer("ImGuiLayer"),
        time(0.0f)
    {

    }

    ImGuiLayer::~ImGuiLayer() = default;

    void ImGuiLayer::onEvent(Event& event)
    {
        if (blockEvents) {
            ImGuiIO& io = getIO();
            event.handled |= event.isInCategory(EVENT_CATEGORY_MOUSE) & io.WantCaptureMouse;
            event.handled |= event.isInCategory(EVENT_CATEGORY_KEYBOARD) & io.WantCaptureKeyboard;
        }
    }

    void ImGuiLayer::onAttach()
    {
        NQ_PROFILE_FUNCTION();

        /// Set up ImGui Context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = getIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        io.Fonts->AddFontFromFileTTF("../NAUQ/res/fonts/OpenSans-Bold.ttf", 18.0f);
        io.FontDefault = io.Fonts->AddFontFromFileTTF("../NAUQ/res/fonts/OpenSans-Regular.ttf", 18.0f);


        /// Setup Dear ImGui Style
//        ImGui::StyleColorsDark();
        setDarkThemeColors();

        /// When viewports are enabled we tweak WindowRounding/WindowBg so platform Windows can look identical to regular ones
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::get();
        auto* glfwWindow = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());

        /// Set up platform/render binding
        ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach()
    {
        NQ_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::begin()
    {
        NQ_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::end()
    {
        NQ_PROFILE_FUNCTION();

        ImGuiIO& io = getIO();
        Window& window = Application::get().getWindow();

        io.DisplaySize = ImVec2(static_cast<float>(window.getWidth()), static_cast<float>(window.getHeight()));

        /// Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);
        }
    }

    void ImGuiLayer::setDarkThemeColors()
    {
        auto& colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = { 0.1f, 0.105f, 0.11f, 1.0f };

        /// Headers
        colors[ImGuiCol_Header] = { 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_HeaderHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_HeaderActive] = { 0.15f, 0.1505f, 0.151f, 1.0f };

        /// Buttons
        colors[ImGuiCol_Button] = { 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_ButtonHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_ButtonActive] = { 0.15f, 0.1505f, 0.151f, 1.0f };

        /// Frame BG
        colors[ImGuiCol_FrameBg] = { 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_FrameBgHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_FrameBgActive] = { 0.15f, 0.1505f, 0.151f, 1.0f };

        /// Tabs
        colors[ImGuiCol_Tab] = { 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TabHovered] = { 0.38f, 0.3805f, 0.381f, 1.0f };
        colors[ImGuiCol_TabActive] = { 0.28f, 0.2805f, 0.281f, 1.0f };
        colors[ImGuiCol_TabUnfocused] = { 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TabUnfocusedActive] = { 0.2f, 0.205f, 0.21f, 1.0f };

        /// Title
        colors[ImGuiCol_TitleBg] = { 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgActive] = { 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgCollapsed] = { 0.15f, 0.1505f, 0.151f, 1.0f };
    }


}