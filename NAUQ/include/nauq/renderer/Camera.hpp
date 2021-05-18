//
// Created by nauq302 on 18/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_CAMERA_HPP
#define NAUQ_GAME_ENGINE_CAMERA_HPP

#include "nauq/core/Core.hpp"

namespace nauq {

    class Camera
    {
    protected:
        glm::mat4 projection;

    public:
        explicit inline Camera() : projection(1.0f) {}
        explicit inline Camera(const glm::mat4& projection) : projection(projection) {}
        virtual ~Camera() = default;

    public:
        [[nodiscard]] inline const glm::mat4& getProjection() const { return projection; }
    };
}




#endif //NAUQ_GAME_ENGINE_CAMERA_HPP
