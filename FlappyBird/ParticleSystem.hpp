//
// Created by nauq302 on 22/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_PARTICLESYSTEM_HPP
#define NAUQ_GAME_ENGINE_PARTICLESYSTEM_HPP


#include <nauq.hpp>

struct ParticleProps
{
    glm::vec2 position;
    glm::vec2 velocity, velocityVariation;
    glm::vec4 colorBegin, colorEnd;
    float sizeBegin, sizeEnd, sizeVariation;
    float lifeTime = 1.0f;
};

class ParticleSystem
{
private:
    struct Particle
    {
        glm::vec2 position;
        glm::vec2 velocity;
        glm::vec4 colorBegin, colorEnd;
        float rotation = 0.0f;
        float sizeBegin, sizeEnd;
        float lifeTime = 1.0f;
        float lifeRemaining = 0.0f;
        bool active = false;
    };

    std::vector<Particle> particlePool;
    std::uint32_t poolIndex = 999;

public:
    explicit ParticleSystem();

public:
    void emit(const ParticleProps& particleProps);
    void onUpdate(nauq::TimeStep ts);
    void onRender();
};


#endif //NAUQ_GAME_ENGINE_PARTICLESYSTEM_HPP
