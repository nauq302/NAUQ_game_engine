//
// Created by nauq302 on 18/05/2021.
//

#include "nauq/scene/SceneCamera.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "nauq/Log.hpp"

namespace nauq {

    void SceneCamera::setPerspective(float verticalFov, float nearClip, float farClip)
    {
        projectionType = ProjectionType::PERSPECTIVE;

        perspectiveFOV = verticalFov;
        perspectiveNear = nearClip;
        perspectiveFar = farClip;

        calculateProjection();
    }

    void SceneCamera::setOrthographic(float size, float nearClip, float farClip)
    {
        projectionType = ProjectionType::ORTHOGRAPHIC;

        orthographicSize = size;
        orthographicNear = nearClip;
        orthographicFar = farClip;

        calculateProjection();
    }

    void SceneCamera::setViewportSize(uint32_t width, uint32_t height)
    {
        aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        calculateProjection();
    }

    void SceneCamera::calculateProjection()
    {
        if (projectionType == ProjectionType::PERSPECTIVE) {
            projection = glm::perspective(perspectiveFOV, aspectRatio, perspectiveNear, perspectiveFar);

        } else {
            float left =  orthographicSize * aspectRatio * -0.5f;
            float right = -left;
            float bottom = orthographicSize * -0.5f;
            float top = -bottom;

            projection = glm::ortho(left, right, bottom, top, orthographicNear, orthographicFar);
        }

//        for (int i = 0; i < 4; ++i) {
//            NQ_INFO("{} , {}, {}, {}", projection[i][0], projection[i][1] , projection[i][2] , projection[i][3]);
//        }
//        NQ_INFO("");
    }




}


