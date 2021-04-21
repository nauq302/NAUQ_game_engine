//
// Created by nauq302 on 16/04/2021.
//

#include "GameLayer.hpp"
#include "Random.hpp"

GameLayer::GameLayer() :
        nauq::Layer("Game Layer")
{
    auto& window = nauq::Application::get().getWindow();
    camera = createCamera(window.getWidth(), window.getHeight());

    Random::init();
}



void GameLayer::onAttach()
{
    level.init();

    auto& io = ImGui::GetIO();
    font = io.Fonts->AddFontFromFileTTF("../../OpenSans-Regular.ttf", 120.0f);
}

void GameLayer::onDetach()
{
}

void GameLayer::onUpdate(nauq::TimeStep ts)
{
    time += ts;

    if (static_cast<int>(time * 10) % 8 > 4) {
        blink = !blink;
    }

    if (level.isGameOver()) {
        state = GameState::GAME_OVER;
    }

    auto playerPos = level.getPlayer().getPosition();
    camera->setPosition({ playerPos.x, playerPos.y, 0.0f });

    switch (state) {
        case GameState::PLAY:
            level.onUpdate(ts);
            break;
        default:;
    }

    nauq::RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
    nauq::RenderCommand::clear();

    nauq::Renderer2D::beginScene(*camera);
    level.onRender();
    nauq::Renderer2D::endScene();

}

void GameLayer::onImGuiRender()
{
    switch (state) {
        case GameState::PLAY: {
            std::uint32_t playerScore = level.getPlayer().getScore();
            std::string scoreStr = "Score: " + std::to_string(playerScore);
            ImGui::GetForegroundDrawList()->AddText(font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
            break;
        }

        case GameState::MAIN_MENU: {
            auto pos = ImGui::GetWindowPos();
            auto width = nauq::Application::get().getWindow().getWidth();
            auto height = nauq::Application::get().getWindow().getHeight();

            pos.x += width * 0.5f - 300.0f;
            pos.y += 50.0f;

            if (blink) {
                ImGui::GetForegroundDrawList()->AddText(font, 120.0f, pos, 0xffffffff, "Click to play");
            }
            break;
        }

        case GameState::GAME_OVER: {
            auto pos = ImGui::GetWindowPos();
            auto width = nauq::Application::get().getWindow().getWidth();
            auto height = nauq::Application::get().getWindow().getHeight();

            pos.x += width * 0.5f - 300.0f;
            pos.y += 50.0f;

            if (blink) {
                ImGui::GetForegroundDrawList()->AddText(font, 120.0f, pos, 0xffffffff, "Click to play");
            }

            pos.x += 200.0f;
            pos.y += 150.0f;

            std::uint32_t playerScore = level.getPlayer().getScore();
            std::string scoreStr = "Score: " + std::to_string(playerScore);
            ImGui::GetForegroundDrawList()->AddText(font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());

            break;
        }

    }
}

void GameLayer::onEvent(nauq::Event& event)
{
    nauq::EventDispatcher dispatcher(event);
    dispatcher.dispatch<nauq::WindowResizeEvent>(NQ_BIND_EVENT_FN(GameLayer::onWindowResize));
    dispatcher.dispatch<nauq::MouseButtonPressEvent>(NQ_BIND_EVENT_FN(GameLayer::onMouseButtonPressed));
}

bool GameLayer::onMouseButtonPressed(nauq::MouseButtonPressEvent& event)
{
    if (state == GameState::GAME_OVER) {
        level.reset();
    }

    state = GameState::PLAY;
    return false;
}

bool GameLayer::onWindowResize(nauq::WindowResizeEvent& event)
{
    camera = createCamera(event.getWidth(), event.getHeight());
    return false;
}


nauq::Scope<nauq::OrthographicCamera> GameLayer::createCamera(unsigned int width, unsigned int height)
{
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    float camWidth = 8.0f;
    float bottom = -camWidth;
    float top = camWidth;
    float left = bottom * aspectRatio;
    float right = top * aspectRatio;

    return nauq::createScope<nauq::OrthographicCamera>(left, right, bottom, top);
}