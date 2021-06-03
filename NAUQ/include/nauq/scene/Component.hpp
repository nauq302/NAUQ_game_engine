//
// Created by nauq302 on 13/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_COMPONENT_HPP
#define NAUQ_GAME_ENGINE_COMPONENT_HPP

#include "nauq/core/Core.hpp"
#include "nauq/core/TimeStep.hpp"
#include "SceneCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <concepts>
#include <functional>

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
        glm::vec3 translate = { 0, 0, 0 };
        glm::vec3 rotation = { 0, 0, 0};
        glm::vec3 scale = { 1, 1, 1 };

    public:
        inline TransformComponent() = default;
//        inline TransformComponent(const glm::mat4& trans) : transform(trans) {}

//        inline operator glm::mat4&() { return transform; }
//        inline operator const glm::mat4&() const { return transform; }
        [[nodiscard]] glm::mat4 getTransform() const
        {
            glm::mat4 rot = glm::rotate(eyes, rotation.x, { 1, 0, 0 })
                          * glm::rotate(eyes, rotation.y, { 0, 1, 0 })
                          * glm::rotate(eyes, rotation.z, { 0, 0, 1 });
            return glm::translate(eyes, translate) * rot * glm::scale(eyes, scale);
        }

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

    class ScriptableEntity;

    struct NativeScriptComponent : Component
    {

        ScriptableEntity* instance = nullptr;

        ScriptableEntity* (*instantiateFn)() = nullptr;
        void (*destroyFn)(NativeScriptComponent*) = nullptr;

        template<typename T>
        void bind()
        {
            instantiateFn = []() { return static_cast<ScriptableEntity*>(new T); };
            destroyFn = [](NativeScriptComponent* nsc) { delete nsc->instance; nsc->instance = nullptr; };
        }

    };

    template <typename C>
    concept ComponentType = std::derived_from<C, Component> && !std::same_as<C,Component>;
}


#endif //NAUQ_GAME_ENGINE_COMPONENT_HPP
