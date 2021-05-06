//
// Created by nauq302 on 12/12/2020.
//

#include "nauq/renderer/OrthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <nauq/debug/Instrumentor.hpp>

namespace nauq {

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) :
        projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
        view(1.0f),
        viewProjection(projection * view)
    {
        NQ_PROFILE_FUNCTION();

    }

    void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
    {
        NQ_PROFILE_FUNCTION();

        projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        viewProjection = projection * view;
    }

    void OrthographicCamera::recalculateView()
    {
        NQ_PROFILE_FUNCTION();

        constexpr glm::mat4 eyes(1.0f);
        glm::mat4 transform = glm::translate(eyes, position) * glm::rotate(eyes, glm::radians(rotation), { 0, 0, 1 });

        view = glm::inverse(transform);
        viewProjection = projection * view;
    }




}