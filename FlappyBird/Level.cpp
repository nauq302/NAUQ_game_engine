//
// Created by nauq302 on 16/04/2021.
//

#include "Level.hpp"
#include <glm/gtx/color_space.hpp>

static const std::size_t NUMBER_OF_PILLARS = 5;

static glm::vec4 hsv2rgba(const glm::vec3& hsv)
{
    auto rgb = glm::rgbColor(hsv);
    return { rgb.r, rgb.g, rgb.b, 1.0f };
}



void Level::init()
{
    triangleTex = nauq::Texture2D::create("../../FlappyBird/res/img/Triangle/png");

    pillars.resize(NUMBER_OF_PILLARS);
    for (int i = 0; i < NUMBER_OF_PILLARS; ++i) {
        createPillar(i, i * 10.0f);
    }
}

void Level::onUpdate(nauq::TimeStep ts)
{

}

void Level::onRender()
{
    auto playerPos = player.getPosition();

    auto color = hsv2rgba(pillarHSV);

    nauq::Renderer2D::drawQuad({ playerPos.x, 0.0f, -0.8f }, { 50.0f, 50.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
}

void Level::onImGuiRender()
{

}

void Level::reset()
{

}

void Level::createPillar(int index, float offset)
{

}

bool Level::isCollision()
{
    return false;
}

void Level::endGame()
{

}
