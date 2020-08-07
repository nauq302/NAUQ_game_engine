//
// Created by nauq302 on 05/08/2020.
//

#include "nauq/Application.hpp"
#include "nauq/events/ApplicationEvent.hpp"
#include "nauq/Log.hpp"

namespace nauq {

    Application::Application() = default;

    Application::~Application() = default;

    void Application::run()
    {
        WindowResizeEvent e(1280, 720);
        NAUQ_TRACE(e.toString());
        while (true);
    }
}