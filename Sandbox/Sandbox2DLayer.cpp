//
// Created by nauq302 on 08/04/2021.
//


#include "Sandbox2DLayer.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <iostream>

template <typename Fn>
class Timer
{
private:
    const char* name;
    std::chrono::time_point<std::chrono::system_clock> start;
    Fn func;
    bool stopped;

public:
    explicit inline Timer(const char* name, Fn&& fn) : name(name), start(std::chrono::high_resolution_clock::now()), func(fn), stopped(false) { }
    inline ~Timer() { if (!stopped) stop(); }

public:
    void stop()
    {
        auto end = std::chrono::high_resolution_clock::now();
        long long s = std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count();
        long long e = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();
        stopped = true;
        double d = (e - s) * 0.001;
        func({ name, d });
    }
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult p) { profileResults.push_back(p); })

Sandbox2DLayer::Sandbox2DLayer() :
    nq::Layer("Sandbox 2D"),
    cameraController(1024.f / 768.f)
{

}

void Sandbox2DLayer::onAttach()
{
    texture = nq::Texture2D::create("../../Sandbox/res/hv.jpeg");
}

void Sandbox2DLayer::onDetach()
{

}

void Sandbox2DLayer::onUpdate(nq::TimeStep ts)
{
    PROFILE_SCOPE("update");

    /// Update
    {
        PROFILE_SCOPE("camera");
        cameraController.onUpdate(ts);
    }


    /// Render
    nq::RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    nq::RenderCommand::clear();

    nq::Renderer2D::beginScene(cameraController.getCamera());

    nq::Renderer2D::drawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    nq::Renderer2D::drawQuad({  0.5f, -0.5f }, { 0.5f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });


    nq::Renderer2D::drawQuad({  0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, texture);


    nq::Renderer2D::endScene();
}

void Sandbox2DLayer::onImGuiRender()
{

    ImGui::Begin("Setting");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(sqColor));

    for (auto& p : profileResults) {
        char labels[50];
        strcat(labels, " %.3fms - ");
        strcpy(labels, p.name);
        ImGui::Text(labels, p.time);
    }
    profileResults.clear();

    ImGui::End();
}

void Sandbox2DLayer::onEvent(nq::Event& event)
{
    cameraController.onEvent(event);
}



