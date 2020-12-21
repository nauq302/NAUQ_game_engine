//
// Created by nauq302 on 12/12/2020.
//

#include "nauq/renderer/OrthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace nauq {

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) :
        projection(glm::ortho(left,right,bottom,top,-1.0f,1.0f)),
        view(1.0f)
    {
        viewProjection = projection * view;
    }

    void OrthographicCamera::recalculateView()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                  * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0,0,1));

        view = glm::inverse(transform);
        viewProjection = projection * view;
    }


}