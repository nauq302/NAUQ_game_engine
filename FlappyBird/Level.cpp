//
// Created by nauq302 on 16/04/2021.
//

#include "Level.hpp"

#include "Random.hpp"

#include <glm/gtx/color_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const std::size_t NUMBER_OF_PILLARS = 5;

static glm::vec4 hsv2rgba(const glm::vec3& hsv)
{
    glm::vec3 c = { hsv.x * 360.f , hsv.y, hsv.z };
    glm::vec3 rgb = glm::rgbColor(c);
    return { rgb.r, rgb.g, rgb.b, 1.0f };
}

static bool pointInTri(glm::vec2 p, glm::vec2 p0, glm::vec2 p1, glm::vec2 p2)
{
    float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
    float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

    if (s < 0 != t < 0)
        return false;

    float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

    return A < 0 ?
           s <= 0 && s + t >= A :
           s >= 0 && s + t <= A;
}

void Level::init()
{
    triangleTex = nauq::Texture2D::create("../../FlappyBird/res/img/Triangle.png");
    player.loadRes();

    pillars.resize(NUMBER_OF_PILLARS);
    for (int i = 0; i < NUMBER_OF_PILLARS; ++i) {
        createPillar(i, i * 10.0f);
    }
}

void Level::onUpdate(nauq::TimeStep ts)
{
    player.onUpdate(ts);

    if (isCollision()) {
        endGame();
        return;
    }

    pillarHSV.x += 0.1f * ts;
    if (pillarHSV.x > 1.0f) {
        pillarHSV.x = 0.0f;
    }

    if (player.getPosition().x > pillarTarget) {
        createPillar(pillarIndex, pillarTarget + 20.0f);
        pillarIndex = (pillarIndex + 1) % pillars.size();
        pillarTarget += 10.0f;
    }
}

void Level::onRender()
{
    glm::vec2 playerPos = player.getPosition();

    glm::vec4 color = hsv2rgba(pillarHSV);

    /// Background
    nauq::Renderer2D::drawQuad({ playerPos.x, 0.0f, -0.8f }, { 50.0f, 50.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

    /// Floor & ceiling
    nauq::Renderer2D::drawQuad({ playerPos.x,  34.0f }, { 50.0f, 50.0f }, color);
    nauq::Renderer2D::drawQuad({ playerPos.x, -34.0f }, { 50.0f, 50.0f }, color);

    for (auto& p : pillars) {
        nauq::Renderer2D::drawRotatedQuad(p.topPos, p.topScale, 180.f, triangleTex, 1.0f, color);
        nauq::Renderer2D::drawRotatedQuad(p.botPos, p.botScale, 0.0f, triangleTex, 1.0f, color);
    }

    player.onRender();
}

void Level::onImGuiRender()
{
    player.onImGuiRender();
}

void Level::reset()
{
    gameOver = false;
    player.reset();

    pillarTarget = 30.0f;
    pillarIndex = 0;

    for (int i = 0; i < 5; ++i) {
        createPillar(i, i * 10.0f);
    }
}

void Level::createPillar(int index, float offset)
{
    Pillar& pillar = pillars[index];

    pillar.topPos.x = offset;
    pillar.botPos.x = offset;

    pillar.topPos.z = index * 0.1f - 0.5f;
    pillar.botPos.z = pillar.topPos.z + 0.05f;

    float center = Random::getFloat() * 35.0f - 17.5f;
    float gap = 2.0f + Random::getFloat() * 5.0f;

    pillar.topPos.y = 10.0f - (10.0f - center) * 0.2f + gap * 0.5f;
    pillar.botPos.y = -10.0f - (10.0f - center) * 0.2f - gap * 0.5f;
}

bool Level::isCollision()
{
    if (glm::abs(player.getPosition().y) > 8.5f) {
        return true;
    }

    glm::vec4 playerVertices[4] = {
            { -0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f,  0.5f, 0.0f, 1.0f },
            { -0.5f,  0.5f, 0.0f, 1.0f }
    };

    auto pos = player.getPosition();
    glm::vec4 playerTransformedVerts[4];

    static const glm::mat4 eyes(1.0f);

    for (int i = 0; i < 4; ++i) {
        playerTransformedVerts[i] = glm::translate(eyes, { pos.x, pos.y, 0.0f })
                * glm::rotate(eyes, glm::radians(player.getRotation()), {0.0f, 0.0f, 1.0f})
                * glm::scale(eyes, { 1.0f, 1.3f, 1.0f })
                * playerVertices[i];
    }

    glm::vec4 pillarVertices[3] = {
            { -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
            {  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
            {  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
    };

    for (auto& p : pillars) {
        glm::vec2 tri[3];

        for (int i = 0; i < 3; ++i) {
            tri[i] = glm::translate(eyes, { p.topPos.x, p.topPos.y, 0.0f })
                    * glm::rotate(eyes, glm::radians(180.0f), { 0.0f, 0.0f, 1.0f })
                    * glm::scale(eyes, { p.topScale.x, p.topScale.y, 1.0f })
                    * pillarVertices[i];
        }

        for (auto& v : playerTransformedVerts) {
            if (pointInTri({ v.x, v.y }, tri[0], tri[1], tri[2])) {
                return true;
            }
        }

        for (int i = 0; i < 3; ++i) {
            tri[i] = glm::translate(eyes, { p.botPos.x, p.botPos.y, 0.0f }) * glm::scale(eyes, { p.botScale.x, p.botScale.y, 1.0f })
                    * pillarVertices[i];
        }

        for (auto& v : playerTransformedVerts) {
            if (pointInTri({ v.x, v.y }, tri[0], tri[1], tri[2])) {
                return true;
            }
        }
    }

    return false;
}

void Level::endGame()
{
    gameOver = true;
}
