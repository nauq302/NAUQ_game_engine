//
// Created by nauq302 on 12/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_ORTHOGRAPHICCAMERA_HPP
#define NAUQ_GAME_ENGINE_ORTHOGRAPHICCAMERA_HPP

#include <glm/glm.hpp>

namespace nauq {

    class OrthographicCamera
    {
    private:
        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 viewProjection;

        glm::vec3 position = { 0.0f, 0.0f, 0.0f };
        float rotation = 0.0f;

    public:
        explicit OrthographicCamera(float left, float right, float bottom, float top);

    public:
        [[nodiscard]] const glm::vec3& getPosition() const { return position; }
        [[nodiscard]] float getRotation() const { return rotation; }
        void setPosition(const glm::vec3& pos) { position = pos; recalculateView(); }
        void setRotation(float degree) { rotation = degree; recalculateView(); }

        [[nodiscard]] const glm::mat4& getProjection() const { return projection; }
        [[nodiscard]] const glm::mat4& getView() const { return view; }
        [[nodiscard]] const glm::mat4& getViewProjection() const { return viewProjection; }

    private:
        void recalculateView();
    };
}




#endif //NAUQ_GAME_ENGINE_ORTHOGRAPHICCAMERA_HPP
