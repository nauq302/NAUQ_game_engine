//
// Created by nauq302 on 18/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_SCENECAMERA_HPP
#define NAUQ_GAME_ENGINE_SCENECAMERA_HPP

#include "nauq/renderer/Camera.hpp"

#include "nauq/Log.hpp"
#include <array>

namespace nauq {

    class SceneCamera :
            public Camera
    {
    public:
        enum class ProjectionType
        {
            PERSPECTIVE = 0,
            ORTHOGRAPHIC = 1
        };

        static constexpr const std::array<const char*,2> PROJECTION_TYPES_S = { "Perspective", "Orthographic" };

    private:
        ProjectionType projectionType = ProjectionType::ORTHOGRAPHIC;

        float perspectiveFOV = glm::radians(45.0f);
        float perspectiveNear = 0.01f;
        float perspectiveFar = 1000.0f;

        float orthographicSize = 10.0f;
        float orthographicNear = -1.0f;
        float orthographicFar = 1.0f;

        float aspectRatio = 0.0f;

    public:
        explicit SceneCamera() { calculateProjection(); }
        ~SceneCamera() override = default;

    public:
        static constexpr const char* projectionType_s(ProjectionType type) { return PROJECTION_TYPES_S[static_cast<int>(type)]; }

        [[nodiscard]] inline ProjectionType getProjectionType() const { return projectionType; }
        inline void setProjectionType(ProjectionType type) { projectionType = type; }
        [[nodiscard]] inline const char* getProjectionType_s() const { return projectionType_s(projectionType); }



        void setPerspective(float verticalFov, float nearClip, float farClip);

        [[nodiscard]] inline float getPerspectiveFov() const { return perspectiveFOV; }
        void setPerspectiveFov(float verticalFov) { perspectiveFOV = verticalFov; calculateProjection(); }

        [[nodiscard]] inline float getPerspectiveNearClip() const { return perspectiveNear; }
        void setPerspectiveNearClip(float nearClip) { perspectiveNear = nearClip; calculateProjection(); }

        [[nodiscard]] inline float getPerspectiveFarClip() const { return perspectiveFar; }
        void setPerspectiveFarClip(float farClip) { perspectiveFar = farClip; calculateProjection(); }


        void setOrthographic(float size, float nearClip, float farClip);

        [[nodiscard]] inline float getOrthographicSize() const { return orthographicSize; }
        void setOrthographicSize(float size) { orthographicSize = size; calculateProjection(); }

        [[nodiscard]] inline float getOrthographicNearClip() const { return orthographicNear; }
        void setOrthographicNearClip(float nearClip) { orthographicNear = nearClip; calculateProjection(); }

        [[nodiscard]] inline float getOrthographicFarClip() const { return orthographicFar; }
        void setOrthographicFarClip(float farClip) { orthographicFar = farClip; calculateProjection(); }

        void setViewportSize(uint32_t width, uint32_t height);

    private:
        void calculateProjection();

    };

}



#endif //NAUQ_GAME_ENGINE_SCENECAMERA_HPP
