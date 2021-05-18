//
// Created by nauq302 on 18/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_SCENECAMERA_HPP
#define NAUQ_GAME_ENGINE_SCENECAMERA_HPP

#include "nauq/renderer/Camera.hpp"

namespace nauq {

    class SceneCamera :
            public Camera
    {
    private:
        float orthographicSize = 10.0f;
        float orthographicNear = -1.0f;
        float orthographicFar = 1.0f;
        float aspectRatio = 0.0f;

    public:
        explicit SceneCamera() { calculateProjection(); }
        ~SceneCamera() override = default;

    public:
        void setOrthographic(float size, float nearClip, float farClip);
        void setViewportSize(uint32_t width, uint32_t height);

    private:
        void calculateProjection();
    };

}



#endif //NAUQ_GAME_ENGINE_SCENECAMERA_HPP
