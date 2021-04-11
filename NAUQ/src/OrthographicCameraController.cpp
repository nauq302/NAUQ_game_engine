//
// Created by nauq302 on 29/12/2020.
//

#include "nauq/OrthographicCameraController.hpp"

#include "nauq/Input.hpp"
#include "nauq/KeyCodes.hpp"

namespace nauq {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotatable) :
            aspectRatio(aspectRatio),
            zoomLevel(1.0f),
            camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel),
            position(0.0f, 0.0f, 0.0f),
            transSpeed(4.0f),
            camRot(0.0f),
            camRotSpeed(45.0f),
            rotatable(rotatable)
    {

    }

    void OrthographicCameraController::onUpdate(TimeStep ts)
    {
        if (Input::isKeyPress(NQ_KEY_A))
            position.x -= transSpeed * ts;

        else if (Input::isKeyPress(NQ_KEY_D))
            position.x += transSpeed * ts;

        else if (Input::isKeyPress(NQ_KEY_S))
            position.y -= transSpeed * ts;

        else if (Input::isKeyPress(NQ_KEY_W))
            position.y += transSpeed * ts;


        if (rotatable) {
            if (Input::isKeyPress(NQ_KEY_Q))
                camRot += camRotSpeed * ts;

            if (Input::isKeyPress(NQ_KEY_E))
                camRot -= camRotSpeed * ts;

            camera.setRotation(camRot);
        }

        camera.setPosition(position);
        transSpeed = zoomLevel;
    }

    void OrthographicCameraController::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseScrollEvent>(NQ_BIND_EVENT_FN(OrthographicCameraController::onMouseScroll));
        dispatcher.dispatch<WindowResizeEvent>(NQ_BIND_EVENT_FN(OrthographicCameraController::onWindowResize));
    }

    bool OrthographicCameraController::onMouseScroll(MouseScrollEvent& e)
    {
        zoomLevel -= e.getYOffset();
        zoomLevel = std::max(zoomLevel, 0.25f);
        camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
        return false;
    }

    bool OrthographicCameraController::onWindowResize(WindowResizeEvent& e)
    {
        aspectRatio = static_cast<float>(e.getWidth()) / static_cast<float>(e.getHeight());
        camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
        return false;
    }
}