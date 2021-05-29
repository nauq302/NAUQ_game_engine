//
// Created by nauq302 on 25/05/2021.
//

#include "SceneHierarchyPanel.hpp"
#include <imgui.h>
#include <nauq/scene/Component.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace nauq {

    void SceneHierarchyPanel::onImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");

        context->reg().each([this](entt::entity e) {
            Entity entity(e, context.get());
            drawEntityNode(entity);
        });

        if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
            selected = Entity();

        ImGui::End();

        ImGui::Begin("Properties");
        if (selected)
            drawComponents(selected);
        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityNode(Entity entity)
    {
        auto& tag = entity.get<TagComponent>().tag;

        ImGuiTreeNodeFlags flags = (entity == selected ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened =  ImGui::TreeNodeEx((void*)(uint64_t)entity.id(), flags, "%s", tag.c_str());

        if (ImGui::IsItemClicked( ))
            selected = entity;

        if (opened)
            ImGui::TreePop();

//        ImGui::TreePop();
    }

    void SceneHierarchyPanel::drawComponents(Entity entity)
    {
        if (entity.has<TagComponent>()) {
            std::string& tag =  entity.get<TagComponent>().tag;

            char buffer[256];
            strcpy(buffer, tag.c_str());

            if (ImGui::InputText("Tag", buffer, sizeof buffer)) {
                tag = buffer;
            }
        }

        if (entity.has<TransformComponent>()) {


            if (ImGui::TreeNodeEx((void*) typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
                glm::mat4& transform = entity.get<TransformComponent>().transform;
                ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

                ImGui::TreePop();
            }


        }


    }

}


