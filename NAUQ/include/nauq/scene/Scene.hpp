//
// Created by nauq302 on 13/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_SCENE_HPP
#define NAUQ_GAME_ENGINE_SCENE_HPP

//#include "entt.hpp"

#include "nauq/core/TimeStep.hpp"
#include "Component.hpp"
#include "../../../dependence/entt/include/entt.hpp"

namespace nauq {

    class Entity;

    class Scene
    {
        friend class Entity;

    private:
        entt::registry registry;
        uint32_t viewportWidth = 0;
        uint32_t viewportHeight = 0;

    public:
        explicit Scene();
        ~Scene();

    public:
        void onUpdate(TimeStep ts);
        void onViewportResize(uint32_t width, uint32_t height);

        Entity createEntity(const std::string& name = "");
        void destroyEntity(Entity entity);

        inline entt::registry& reg() { return registry; }

    private:
        template<ComponentType C>
        void onAddComponent(Entity entity, C& component);

    };
}



#endif //NAUQ_GAME_ENGINE_SCENE_HPP
