//
// Created by nauq302 on 25/05/2021.
//

#include "SceneHierarchyPanel.hpp"
#include <imgui.h>
#include <imgui_internal.h>
#include <nauq/scene/Component.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace nauq {

    static bool drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);

    template <ComponentType C, typename UIFunc>
    static void drawComponent(const std::string& name, Entity entity, bool removable, UIFunc uiFunc);



    void SceneHierarchyPanel::onImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");

        context->reg().each([this](entt::entity e) {
            Entity entity(e, context.get());
            drawEntityNode(entity);
        });

        if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
            selectedEntity = Entity::null();

        if (ImGui::BeginPopupContextWindow(nullptr, 1, false)) {
            if (ImGui::MenuItem("Create Empty Entity"))
                context->createEntity("Empty Entity");
            ImGui::EndPopup();
        }

        ImGui::End();

        ImGui::Begin("Properties");
        if (selectedEntity) {
            drawComponents(selectedEntity);


        }
        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityNode(Entity entity)
    {
        auto& tag = entity.get<TagComponent>().tag;

        ImGuiTreeNodeFlags flags = (entity == selectedEntity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        bool opened =  ImGui::TreeNodeEx((void*)(uint64_t)entity.id(), flags, "%s", tag.c_str());

        if (ImGui::IsItemClicked( ))
            selectedEntity = entity;

        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete Entity"))
                entityDeleted = true;
            ImGui::EndPopup();
        }

        if (opened)
            ImGui::TreePop();

        if (entityDeleted) {
            context->destroyEntity(entity);
            if (selectedEntity == entity)
                selectedEntity = Entity::null();
        }
    }

    void SceneHierarchyPanel::drawComponents(Entity entity)
    {
        if (entity.has<TagComponent>()) {
            std::string& tag =  entity.get<TagComponent>().tag;

            char buffer[256];
            strcpy(buffer, tag.c_str());

            if (ImGui::InputText("##Tag", buffer, sizeof buffer)) {
                tag = buffer;
            }
        }

        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");

        if (ImGui::BeginPopup("AddComponent")) {
            if (ImGui::MenuItem("Camera")) {
                selectedEntity.add<CameraComponent>();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::MenuItem("SpriteRenderer")) {
                selectedEntity.add<SpriteRendererComponent>();
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        ImGui::PopItemWidth();

        if (entity.has<TransformComponent>()) {
            drawComponent<TransformComponent>("Transform", entity, false, [](auto& tc) {
                drawVec3Control("Translate", tc.translate);
                glm::vec3 rot = glm::degrees(tc.rotation);
                drawVec3Control("Rotation", rot);
                tc.rotation = glm::radians(rot);
                drawVec3Control("Scale", tc.scale, 1);
            });
        }

        if (entity.has<CameraComponent>()) {
            drawComponent<CameraComponent>("Camera", entity, true, [](auto& cc) {
                SceneCamera& camera = cc.camera;

                ImGui::Checkbox("Primary", &cc.primary);

                auto projectionTypes_s = SceneCamera::PROJECTION_TYPES_S;
                const char* currentProjectionType_s = camera.getProjectionType_s();
                if (ImGui::BeginCombo("Projection", currentProjectionType_s)) {

                    for (int i = 0; i < 2; ++i) {
                        bool selected = currentProjectionType_s == projectionTypes_s[i];
                        if (ImGui::Selectable(projectionTypes_s[i], selected)) {
                            currentProjectionType_s = projectionTypes_s[i];
                            camera.setProjectionType(static_cast<SceneCamera::ProjectionType>(i));
                        }

                        if (selected)
                            ImGui::SetItemDefaultFocus();
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

                    ImGui::Checkbox("Fixed aspect ratio", &cc.fixedAspectRatio);
                }
            });
        }

        if (entity.has<SpriteRendererComponent>()) {
            drawComponent<SpriteRendererComponent>("Sprite Renderer", entity, true, [](auto& src) {
                ImGui::ColorEdit4("Color", glm::value_ptr(src.color));
            });
        }

    }

    bool drawVec3Control(const std::string& label, glm::vec3& values, float resetValue, float columnWidth)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto* boldFont = io.Fonts->Fonts[0];

        bool modify = false;
        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text("%s", label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        modify |= ImGui::DragFloat("##X", &values.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        modify |= ImGui::DragFloat("##Y", &values.y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2f, 0.3f, 0.9f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        modify |= ImGui::DragFloat("##Z", &values.z, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PopStyleVar();

        ImGui::Columns(1);
        ImGui::PopID();
        return modify;
    }

    template <ComponentType C, typename UIFunc>
    void drawComponent(const std::string& name, Entity entity, bool removable, UIFunc uiFunc)
    {
        constexpr ImGuiTreeNodeFlags TREE_NODE_FLAG = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
                ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

        ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4, 4 });
        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2;
        ImGui::Separator();
        bool opened = ImGui::TreeNodeEx((void*) typeid(C).hash_code(), TREE_NODE_FLAG, "%s", name.c_str());

        ImGui::SameLine(contentRegionAvail.x - lineHeight * 0.5f);
        ImGui::PopStyleVar();

        if (ImGui::Button("+", { 20, 20 }))
            ImGui::OpenPopup("ComponentSettings");

        bool removed = false;
        if (ImGui::BeginPopup("ComponentSettings")) {
            if (removable && ImGui::MenuItem("Remove Component"))
                removed = true;
            ImGui::EndPopup();
        }

        if (opened) {
            uiFunc(entity.template get<C>());
            ImGui::TreePop();
        }

        if (removable && removed)
            entity.remove<SpriteRendererComponent>();
    }


}


