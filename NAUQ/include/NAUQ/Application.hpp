//
// Created by nauq302 on 05/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_APPLICATION_HPP
#define NAUQ_GAME_ENGINE_APPLICATION_HPP

#include "Core.hpp"

namespace nauq {

    class NAUQ_API Application
    {
    public:
        explicit Application();
        virtual ~Application();

    public:
        virtual void run();

    };

    Application* createApp();
}



#endif //NAUQ_GAME_ENGINE_APPLICATION_HPP
