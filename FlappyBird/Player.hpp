//
// Created by nauq302 on 18/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_PLAYER_HPP
#define NAUQ_GAME_ENGINE_PLAYER_HPP

#include <nauq.hpp>

#include "ParticleSystem.hpp"

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

    ParticleProps smokeProps, engineProps;
    ParticleSystem particleSystem;

    nauq::Ref<nauq::Texture2D> shipTexture;

public:
    explicit Player();

public:
    [[nodiscard]] glm::vec2 getPosition() const { return position; }
    [[nodiscard]] inline std::uint32_t getScore() const { return static_cast<std::uint32_t>(position.x + 10.0f) / 10.0f; }
    [[nodiscard]] inline float getRotation() const { return velocity.y * 4.0f - 90.0f; }

    void loadRes();
    void onUpdate(nauq::TimeStep ts);
    void onRender();
    void onImGuiRender();
    void reset();

private:

};


#endif //NAUQ_GAME_ENGINE_PLAYER_HPP
