//
// Created by nauq302 on 05/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_APPLICATION_HPP
#define NAUQ_GAME_ENGINE_APPLICATION_HPP

#include "Window.hpp"
#include "LayerStack.hpp"
#include "events/ApplicationEvent.hpp"

#include <memory>

namespace nauq {

    /**
     *  @class Application
     */
    class NAUQ_API Application
    {
    private:
        static inline Application* instance = nullptr;

        std::unique_ptr<Window> window;
        LayerStack layerStack;
        bool running;

    public:
        explicit Application();
        virtual ~Application();

    public:
        static inline Application& get() { return *instance; }

        virtual void run();
        void onEvent(Event& event);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);

        inline Window& getWindow() { return *window; }

    private:
        bool onWindowClosed(WindowCloseEvent& event);
    };

    Application* createApp();
}



#endif //NAUQ_GAME_ENGINE_APPLICATION_HPP
