//
// Created by nauq302 on 13/05/2021.
//

#include "nauq/scene/Scene.hpp"

#include "nauq/core/Core.hpp"
#include "nauq/scene/Component.hpp"
#include "nauq/scene/Entity.hpp"
#include "nauq/scene/ScriptableEntity.hpp"
#include "nauq/renderer/Renderer2D.hpp"


namespace nauq {

    static void doMath(const glm::mat4& transform)
    {

    }

    Scene::Scene()
    {

    }

    Scene::~Scene()
    {

    }

    void Scene::onUpdate(TimeStep ts)
    {
        {
            registry.view<NativeScriptComponent>().each([=, this](entt::entity e, NativeScriptComponent& nsc) {
                if (!nsc.instance) {
                    nsc.instance = nsc.instantiateFn();
                    nsc.instance->entity = Entity(e, this);
                    nsc.instance->onCreate();
                }

                nsc.instance->onUpdate(ts);
            });
        }

        Camera* mainCamera = nullptr;
        glm::mat4 camTransform;
        auto view = registry.view<TransformComponent, CameraComponent>();
        for (auto e : view) {
            auto [tr, c] = view.get<TransformComponent, CameraComponent>(e);
            if (c.primary) {
                mainCamera = &c.camera;
                camTransform = tr.getTransform();
                break;
            }
        }

        if (mainCamera) {
            Renderer2D::beginScene(*mainCamera, camTransform);
            auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

            for (auto e : group) {
                const auto& [trans, sprite] = group.get<TransformComponent, SpriteRendererComponent>(e);
                Renderer2D::drawQuad(trans.getTransform(), sprite);
            }

            Renderer2D::endScene();
        }
    }

    void Scene::onViewportResize(uint32_t width, uint32_t height)
    {
        viewportWidth = width;
        viewportHeight = height;

        auto view = registry.view<CameraComponent>();
        for (auto e : view) {
            auto& cc = view.get<CameraComponent>(e);

            if (!cc.fixedAspectRatio)
                cc.camera.setViewportSize(width, height);
        }
    }

    Entity Scene::createEntity(const std::string& name)
    {
        Entity entity(registry.create(), this);
        entity.add<TransformComponent>();
        entity.add<TagComponent>(name.empty() ? "Unnamed Entity" : name);

        return entity;
    }

    void Scene::destroyEntity(Entity entity)
    {
        registry.destroy(entity);
    }

    template<ComponentType C>
    void Scene::onAddComponent(Entity entity, C& component)
    {

    }

    template<>
    void Scene::onAddComponent(Entity entity, TagComponent& component)
    {

    }

    template<>
    void Scene::onAddComponent(Entity entity, TransformComponent& component)
    {

    }

    template<>
    void Scene::onAddComponent(Entity entity, CameraComponent& component)
    {
        component.camera.setViewportSize(viewportWidth, viewportHeight);
    }

    template<>
    void Scene::onAddComponent(Entity entity, SpriteRendererComponent& component)
    {

    }

    template<>
    void Scene::onAddComponent(Entity entity, NativeScriptComponent& component)
    {

    }
}