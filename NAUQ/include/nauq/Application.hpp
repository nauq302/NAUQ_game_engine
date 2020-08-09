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
        std::unique_ptr<Window> window;
        LayerStack layerStack;
        bool running;

    public:
        explicit Application();
        virtual ~Application();

    public:
        virtual void run();
        void onEvent(Event& event);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);

    private:
        bool onWindowClosed(WindowCloseEvent& event);
    };

    Application* createApp();
}



#endif //NAUQ_GAME_ENGINE_APPLICATION_HPP
