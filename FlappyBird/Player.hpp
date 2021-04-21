//
// Created by nauq302 on 18/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_PLAYER_HPP
#define NAUQ_GAME_ENGINE_PLAYER_HPP

#include <nauq.hpp>

class Player
{
private:
    glm::vec2 position = { -10.0f, 0.0f };
    glm::vec2 velocity = {   5.0f, 0.0f };

    float enginePower = 0.5f;
    float gravity = 0.4f;

    float time = 0.0f;
    float smokeEmitInterval = 0.4f;
    float smokeNextEmitTime = smokeEmitInterval;



public:
    [[nodiscard]] glm::vec2 getPosition() const { return position; }
    [[nodiscard]] std::uint32_t getScore() const { return static_cast<std::uint32_t>(position.x + 10.0f) / 10; }
};


#endif //NAUQ_GAME_ENGINE_PLAYER_HPP
