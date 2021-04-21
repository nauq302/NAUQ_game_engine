//
// Created by nauq302 on 10/08/2020.
//

#include "nauq/imGui/ImGuiLayer.hpp"

#include "imgui.h"

#include "nauq/imGui/ImGuiImpl.hpp"
#include "nauq/Application.hpp"
#include "nauq/debug/Instrumentor.hpp"

namespace nauq {

    ImGuiLayer::ImGuiLayer() :
        Layer("ImGuiLayer"),
        time(0.0f)
    {

    }

    ImGuiLayer::~ImGuiLayer() = default;

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

        /// Setup Dear ImGui Style
        ImGui::StyleColorsDark();

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
        Application& app = Application::get();

        io.DisplaySize = ImVec2(
                static_cast<float>(app.getWindow().getWidth()),
                static_cast<float>(app.getWindow().getHeight()));

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




}