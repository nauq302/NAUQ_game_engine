//
// Created by nauq302 on 16/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_ENTITY_HPP
#define NAUQ_GAME_ENGINE_ENTITY_HPP

#include "nauq/core/Log.hpp"
#include "nauq/scene/Component.hpp"
#include "nauq/scene/Scene.hpp"
#include "../../../dependence/entt/include/entt.hpp"


namespace nauq {

    class Scene;

    class Entity
    {
    private:
        entt::entity entity;
        Scene* scene;

    public:
        explicit inline Entity() : entity(entt::null), scene(nullptr) {}
        explicit inline Entity(entt::entity entityHandle, Scene* scene) : entity(entityHandle), scene(scene) {}

    public:
        static inline Entity null() { return Entity(); }

        [[nodiscard]] inline uint32_t id() const { return static_cast<uint32_t>(entity); }
        inline operator bool() const { return entity != entt::null; }
        inline operator entt::entity() const { return entity; }
        bool operator ==(const Entity& other) const { return entity == other.entity && scene == other.scene; }

        template<ComponentType C>
        C& get() {
            NQ_CORE_ASSERT(has<C>(), "Entity does NOT have component");
            return scene->registry.template get<C>(entity);
        }

        template<ComponentType C>
        const C& get() const {
            NQ_CORE_ASSERT(has<C>(), "Entity does NOT have component");
            return scene->registry.template get<C>(entity);
        }

        template<ComponentType C>
        [[nodiscard]] inline bool has() const { return scene->registry.template any_of<C>(entity); }

        template<ComponentType C, typename... Ts>
        C& add(Ts&&... args) {
            NQ_CORE_ASSERT(!has<C>(), "Entity ALREADY has component");
            C& c = scene->registry.template emplace<C>(entity, std::forward<Ts>(args)...);
            scene->template onAddComponent<C>(*this, c);
            return c;
        }

        template<ComponentType C>
        void remove()
        {
            NQ_CORE_ASSERT(has<C>(), "Entity does NOT have component");
            scene->registry.template remove<C>(entity);
        }
    };



}



#endif //NAUQ_GAME_ENGINE_ENTITY_HPP
