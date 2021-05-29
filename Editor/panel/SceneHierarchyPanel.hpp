//
// Created by nauq302 on 25/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_SCENEHIERARCHYPANEL_HPP
#define NAUQ_GAME_ENGINE_SCENEHIERARCHYPANEL_HPP

#include <nauq/core/Core.hpp>
#include <nauq/scene/Scene.hpp>
#include <nauq/scene/Entity.hpp>

namespace nauq {


    class SceneHierarchyPanel
    {
    private:
        Ref<Scene> context;
        Entity selected;

    public:
        explicit SceneHierarchyPanel() = default;
        explicit SceneHierarchyPanel(const Ref<Scene>& scene) : context(scene) {}

    public:
        void setContext(const Ref<Scene>& scene) { context = scene; }
        void onImGuiRender();

    private:
        void drawEntityNode(Entity entity);
        void drawComponents(Entity entity);
    };
}




#endif //NAUQ_GAME_ENGINE_SCENEHIERARCHYPANEL_HPP
