//
// Created by nauq302 on 16/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_GAMELAYER_HPP
#define NAUQ_GAME_ENGINE_GAMELAYER_HPP

#include "Level.hpp"

#include <nauq.hpp>

class GameLayer :
        public nauq::Layer
{
private:
    enum class GameState {
        PLAY = 0,
        MAIN_MENU = 1,
        GAME_OVER = 2
    };


    nauq::Scope<nauq::OrthographicCamera> camera;
    Level level;
    ImFont* font;
    float time = 0.0f;
    bool blink = false;
    GameState state = GameState::MAIN_MENU;

public:
    explicit GameLayer();

public:
    void onAttach() override;
    void onDetach() override;

    void onUpdate(nauq::TimeStep ts) override;
    void onImGuiRender() override;

    void onEvent(nauq::Event& event) override;

    bool onWindowResize(nauq::WindowResizeEvent& event);
    bool onMouseButtonPressed(nauq::MouseButtonPressEvent& event);

private:
    static nauq::Scope<nauq::OrthographicCamera> createCamera(unsigned width, unsigned height);
};


#endif //NAUQ_GAME_ENGINE_GAMELAYER_HPP
