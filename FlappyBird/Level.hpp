//
// Created by nauq302 on 16/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_LEVEL_HPP
#define NAUQ_GAME_ENGINE_LEVEL_HPP

#include "Player.hpp"

#include <nauq.hpp>

struct Pillar
{
    glm::vec3 topPos = { 0.0f, 10.0f, 0.0f };
    glm::vec2 topScale = { 15.0f, 20.0f };

    glm::vec3 botPos = { 10.0f, 10.0f, 0.0f };
    glm::vec2 botScale = { 15.0f, 20.0f };
};

class Level
{
private:
    Player player;
    nauq::Ref<nauq::Texture2D> triangleTex;
    std::vector<Pillar> pillars;
    float pillarTarget = 30.0f;
    int pillarIndex = 0;
    glm::vec3 pillarHSV = { 0.0f, 0.8f, 0.8f };
    bool gameOver = false;

public:
    [[nodiscard]] bool inline isGameOver() const { return gameOver; }
    Player& getPlayer() { return player; }

    void init();

    void onUpdate(nauq::TimeStep ts);
    void onRender();
    void onImGuiRender();
    void reset();

private:
    void createPillar(int index, float offset);
    bool isCollision();
    void endGame();

};


#endif //NAUQ_GAME_ENGINE_LEVEL_HPP
