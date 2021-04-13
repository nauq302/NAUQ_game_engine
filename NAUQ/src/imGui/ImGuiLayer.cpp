//
// Created by nauq302 on 10/08/2020.
//

#include "nauq/imGui/ImGuiLayer.hpp"

#include "imgui.h"

#include "nauq/imGui/ImGuiImpl.hpp"
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
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = getIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::get();
        auto* glfwWindow = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }




    void ImGuiLayer::begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::end()
    {
        ImGuiIO& io = getIO();
        Application& app = Application::get();

        io.DisplaySize = ImVec2(
                static_cast<float>(app.getWindow().getWidth()),
                static_cast<float>(app.getWindow().getHeight()));

        // Rendering
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