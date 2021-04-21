//
// Created by nauq302 on 16/04/2021.
//

#include <nauq.hpp>
#include <nauq/EntryPoint.hpp>

#include "GameLayer.hpp"

class FlappyBird :
        public nauq::Application
{
public:
    explicit FlappyBird() {
        pushLayer(new GameLayer);
    }

    ~FlappyBird() override = default;

};

nauq::Application* nauq::createApp()
{
    return new FlappyBird();
}

