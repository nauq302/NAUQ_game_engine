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
            selectedEntity = Entity();

        ImGui::End();

        ImGui::Begin("Properties");
        if (selectedEntity)
            drawComponents(selectedEntity);
        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityNode(Entity entity)
    {
        auto& tag = entity.get<TagComponent>().tag;

        ImGuiTreeNodeFlags flags = (entity == selectedEntity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened =  ImGui::TreeNodeEx((void*)(uint64_t)entity.id(), flags, "%s", tag.c_str());

        if (ImGui::IsItemClicked( ))
            selectedEntity = entity;

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

        if (entity.has<CameraComponent>()) {
            if (ImGui::TreeNodeEx((void*) typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera")) {
                auto& cc = entity.get<CameraComponent>();
                SceneCamera& camera = cc.camera;

                auto projectionTypes_s = SceneCamera::PROJECTION_TYPES_S;
                const char* currentProjectionType_s = camera.getProjectionType_s();
                if (ImGui::BeginCombo("Projection", currentProjectionType_s)) {

                    for (int i = 0; i < 2; ++i) {
                        bool selected = currentProjectionType_s == projectionTypes_s[i];
                        if (ImGui::Selectable(projectionTypes_s[i], selected)) {
                            currentProjectionType_s = projectionTypes_s[i];
                            camera.setProjectionType(static_cast<SceneCamera::ProjectionType>(i));
                        }

                        if (selected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }

                    ImGui::EndCombo();
                }

                if (camera.getProjectionType() == SceneCamera::ProjectionType::PERSPECTIVE) {
                    if (float fov = glm::degrees(camera.getPerspectiveFov()); ImGui::DragFloat("Vertical FOV", &fov))
                        camera.setPerspectiveFov(glm::radians(fov));

                    if (float near = camera.getPerspectiveNearClip(); ImGui::DragFloat("Near clip", &near))
                        camera.setPerspectiveNearClip(near);

                    if (float far = camera.getPerspectiveFarClip(); ImGui::DragFloat("Far clip", &far))
                        camera.setPerspectiveFarClip(far);
                }

                if (camera.getProjectionType() == SceneCamera::ProjectionType::ORTHOGRAPHIC) {
                    if (float size = camera.getOrthographicSize(); ImGui::DragFloat("Size", &size))
                        camera.setOrthographicSize(size);

                    if (float near = camera.getOrthographicNearClip(); ImGui::DragFloat("Near clip", &near))
                        camera.setOrthographicNearClip(near);

                    if (float far = camera.getOrthographicFarClip(); ImGui::DragFloat("Far clip", &far))
                        camera.setOrthographicFarClip(far);
                }

                ImGui::TreePop();
            }
        }

    }

}


