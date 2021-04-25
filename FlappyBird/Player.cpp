//
// Created by nauq302 on 18/04/2021.
//

#include "Player.hpp"

#include <glm/gtc/matrix_transform.hpp>

Player::Player() :
        smokeProps {
            .position = { 0.0f, 0.0f },
            .velocity = { -2.0f, 0.0f },
            .velocityVariation = { 4.0f, 2.0f },
            .colorBegin = { 0.8f, 0.8f, 0.8f, 1.0f },
            .colorEnd = { 0.6f, 0.6f, 0.6f, 1.0f },
            .sizeBegin = 0.35f,
            .sizeEnd = 0.0f,
            .sizeVariation = 0.15f,
            .lifeTime = 4.0f
        }, engineProps {
            .position = { 0.0f, 0.0f },
            .velocity = { -2.0f, 0.0f },
            .velocityVariation = { 3.0f, 1.0f },
            .colorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f },
            .colorEnd = { 0.6f, 0.6f, 0.6f, 1.0f },
            .sizeBegin = 0.5f,
            .sizeEnd = 0.0f,
            .sizeVariation = 0.3f,
            .lifeTime = 1.0f
        }
{

}

void Player::loadRes()
{
    shipTexture = nauq::Texture2D::create("../../FlappyBird/res/img/Ship.png");
}


void Player::onUpdate(nauq::TimeStep ts)
{
    time += ts;

    if (nauq::Input::isKeyPress(NQ_KEY_SPACE)) {
        velocity.y += enginePower;
        if (velocity.y < 0.0f) {
            velocity.y += enginePower * 2.0f;
        }

        /// Flames
        glm::vec2 emissionPoint = { 0.0f, -0.6f };
        float rotation = glm::radians(getRotation());
        glm::vec4 rotated = glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::vec4(emissionPoint, 0.0f, 1.0f);
        engineProps.position = position + glm::vec2{ rotated.x, rotated.y };
        engineProps.velocity.y = -velocity.y * 0.2f - 0.2f;
        particleSystem.emit(engineProps);

    } else {
        velocity.y -= gravity;
    }

    velocity.y = glm::clamp(velocity.y, -20.0f, 20.0f);
    position += velocity * static_cast<float>(ts);

    /// Particles
    if (time > smokeNextEmitTime) {
        smokeProps.position = position;
        particleSystem.emit(smokeProps);
        smokeNextEmitTime += smokeEmitInterval;
    }

    particleSystem.onUpdate(ts);
}

void Player::onRender()
{
    particleSystem.onRender();
    nauq::Renderer2D::drawQuad({ position.x, position.y, 0.5f }, { 1.0f, 1.3f }, glm::radians(getRotation()), shipTexture);
}

void Player::onImGuiRender()
{
    ImGui::DragFloat("Engine Power", &enginePower, 0.1f);
    ImGui::DragFloat("Gravity", &gravity, 0.1f);
}

void Player::reset()
{
    position = { -10.0f, 0.0f };
    velocity = { 5.0f, 0.0f };
}

