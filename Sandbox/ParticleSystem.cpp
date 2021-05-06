//
// Created by nauq302 on 22/04/2021.
//

#include "ParticleSystem.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>
#include <random>

class Random
{
private:
    static inline std::mt19937 randomEngine;
    static inline std::uniform_int_distribution<std::mt19937::result_type> distribution;

public:
    static inline void init() { randomEngine.seed(std::random_device()()); }
    static inline float getFloat() {
        return static_cast<float>(distribution(randomEngine)) / static_cast<float>(std::numeric_limits<std::mt19937::result_type>::max());
    }

};

static inline float randomFloat() { return Random::getFloat() - 0.5f; }

ParticleSystem::ParticleSystem(std::size_t maxParticle) :
    particlePool(maxParticle),
    poolIndex(maxParticle - 1)
{
}

void ParticleSystem::emit(const ParticleProps& particleProps)
{
    NQ_INFO("{0}", poolIndex);
    auto& particle = particlePool[poolIndex];
    particle.active = true;
    particle.position = particleProps.position;
    particle.rotation = Random::getFloat() * 2.0f * glm::pi<float>();

    /// Velocity
    particle.velocity = particleProps.velocity;
    particle.velocity.x += particleProps.velocityVariation.x * randomFloat();
    particle.velocity.y += particleProps.velocityVariation.y * randomFloat();

    /// Color
    particle.colorBegin = particleProps.colorBegin;
    particle.colorEnd = particleProps.colorEnd;

    /// Size
    particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation * randomFloat();
    particle.sizeEnd = particle.sizeEnd;

    /// Life
    particle.lifeTime = particleProps.lifeTime;
    particle.lifeRemaining = particleProps.lifeTime;

    poolIndex = (poolIndex + 1) % particlePool.size();
}

void ParticleSystem::onUpdate(nauq::TimeStep ts)
{
    for (auto& p : particlePool) {
        if (!p.active) {
            continue;
        }

        if (p.lifeRemaining <= 0.0f) {
            p.active = false;
            continue;
        }

        p.lifeRemaining -= ts;
        p.position += p.velocity * static_cast<float>(ts);
        p.rotation += 0.01f * ts;
    }
}

void ParticleSystem::onRender(nauq::OrthographicCamera& camera)
{
    nauq::Renderer2D::beginScene(camera);
    for (auto& p : particlePool) {
        if (!p.active) {
            continue;
        }

        float life = p.lifeRemaining / p.lifeTime;
        glm::vec4 color = glm::lerp(p.colorEnd, p.colorBegin, life);
        color.a *= life;

        float size = glm::lerp(p.sizeEnd, p.sizeBegin, life);
        nauq::Renderer2D::drawRotatedQuad(p.position, { size, size }, p.rotation, color);
    }
    nauq::Renderer2D::endScene();
}
