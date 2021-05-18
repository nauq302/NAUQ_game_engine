//
// Created by nauq302 on 13/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_COMPONENT_HPP
#define NAUQ_GAME_ENGINE_COMPONENT_HPP

#include "nauq/core/Core.hpp"
#include "SceneCamera.hpp"

#include <concepts>

namespace nauq {

    struct Component {};

    struct TagComponent : Component
    {
    public:
        std::string tag;

        inline TagComponent() = default;
        inline TagComponent(std::string tag) : tag(std::move(tag)) {}

    };

    struct TransformComponent : Component
    {
    public:
        glm::mat4 transform = eyes;

    public:
        inline TransformComponent() = default;
        inline TransformComponent(const glm::mat4& trans) : transform(trans) {}

        inline operator glm::mat4&() { return transform; }
        inline operator const glm::mat4&() const { return transform; }
    };


    struct SpriteRendererComponent : Component
    {
    public:
        glm::vec4 color = white;

    public:
        inline SpriteRendererComponent() = default;
        inline SpriteRendererComponent(const glm::vec4& color) : color(color) {}

        inline operator glm::vec4&() { return color; }
        inline operator const glm::vec4&() const { return color; }
    };

    struct CameraComponent : Component
    {
        SceneCamera camera;
        bool primary = true;
        bool fixedAspectRatio = false;

        inline CameraComponent() = default;
    };

    template <typename C>
    concept ComponentType = std::derived_from<C, Component>;
}


#endif //NAUQ_GAME_ENGINE_COMPONENT_HPP
