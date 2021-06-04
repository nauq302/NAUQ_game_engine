//
// Created by nauq302 on 05/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_APPLICATION_HPP
#define NAUQ_GAME_ENGINE_APPLICATION_HPP

#include "Window.hpp"
#include "LayerStack.hpp"
#include "nauq/imGui/ImGuiLayer.hpp"
#include "nauq/events/ApplicationEvent.hpp"
#include "nauq/renderer/Shader.hpp"
#include "nauq/renderer/Buffer.hpp"
#include "nauq/renderer/VertexArray.hpp"
#include "nauq/renderer/OrthographicCamera.hpp"

#include <memory>
#include <nauq/core/TimeStep.hpp>

namespace nauq {

    /**
     *  @class Application
     */
    class NAUQ_API Application
    {
    private:
        static inline Application* instance = nullptr;

        std::unique_ptr<Window> window;
        ImGuiLayer* imGuiLayer;
        LayerStack layerStack;
        float lastFrameTime;
        bool running;
        bool minimized;

    public:
        explicit Application(const std::string& name = "Nauq Engine");
        virtual ~Application();

    public:
        static inline Application& get() { return *instance; }

        virtual void run();
        void onEvent(Event& event);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);

        inline void close() { running = false; }

        inline Window& getWindow() { return *window; }
        inline ImGuiLayer* getImGuiLayer() { return imGuiLayer; }
    private:
        bool onWindowClosed(WindowCloseEvent& event);
        bool onWindowResized(WindowResizeEvent& event);
    };

    Application* createApp();
}



#endif //NAUQ_GAME_ENGINE_APPLICATION_HPP
