//
// Created by nauq302 on 29/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_ORTHOGRAPHICCAMERACONTROLLER_HPP
#define NAUQ_GAME_ENGINE_ORTHOGRAPHICCAMERACONTROLLER_HPP

#include "nauq/core/TimeStep.hpp"
#include "nauq/renderer/OrthographicCamera.hpp"

#include "nauq/events/ApplicationEvent.hpp"
#include "nauq/events/MouseEvent.hpp"

namespace nauq {


    class OrthographicCameraController
    {
    private:
        float aspectRatio;
        float zoomLevel;
        OrthographicCamera camera;

        glm::vec3 camPos;
        float camTransSpeed;

        float camRot;
        float camRotSpeed;
        
        bool rotatable;


    public:
        explicit OrthographicCameraController(float aspectRatio, bool rotatable = false);

    public:
        inline OrthographicCamera& getCamera() { return camera; }
        [[nodiscard]] inline const OrthographicCamera& getCamera() const { return camera; }

        void onUpdate(TimeStep ts);
        void onEvent(Event& event);

    private:
        bool onMouseScroll(MouseScrollEvent& e);
        bool onWindowResize(WindowResizeEvent& e);

    };
}




#endif //NAUQ_GAME_ENGINE_ORTHOGRAPHICCAMERACONTROLLER_HPP
