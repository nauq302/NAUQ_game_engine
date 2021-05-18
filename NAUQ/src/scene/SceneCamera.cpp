//
// Created by nauq302 on 18/05/2021.
//

#include "nauq/scene/SceneCamera.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace nauq {

    void SceneCamera::setOrthographic(float size, float nearClip, float farClip)
    {
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
        float left =  orthographicSize * aspectRatio * -0.5f;
        float right = -left;
        float bottom = orthographicSize * -0.5f;
        float top = -bottom;

        projection = glm::ortho(left, right, bottom, top, orthographicNear, orthographicFar);
    }

}


