//
// Created by nauq302 on 29/12/2020.
//

#include <nauq/debug/Instrumentor.hpp>
#include "nauq/OrthographicCameraController.hpp"

#include "nauq/Input.hpp"
#include "nauq/KeyCodes.hpp"

namespace nauq {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotatable) :
            aspectRatio(aspectRatio),
            zoomLevel(1.0f),
            bounds { -aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel },
            camera(bounds.left, bounds.right, bounds.bottom, bounds.top),
            camPos(0.0f, 0.0f, 0.0f),
            transSpeed(4.0f),
            camRot(0.0f),
            camRotSpeed(45.0f),
            rotatable(rotatable)
    {

    }

    void OrthographicCameraController::onUpdate(TimeStep ts)
    {
        NQ_PROFILE_FUNCTION();

        float rad = glm::radians(camRot);
        auto trans = transSpeed * ts;

        if (Input::isKeyPress(NQ_KEY_A)) {
            camPos.x -= glm::cos(rad) * trans;
            camPos.y -= glm::sin(rad) * trans;

        } else if (Input::isKeyPress(NQ_KEY_D)) {
            camPos.x += glm::cos(rad) * trans;
            camPos.y += glm::sin(rad) * trans;

        } else if (Input::isKeyPress(NQ_KEY_S)) {
            camPos.x += glm::sin(rad) * trans;
            camPos.y -= glm::cos(rad) * trans;

        } else if (Input::isKeyPress(NQ_KEY_W)) {
            camPos.x -= glm::sin(rad) * trans;
            camPos.y += glm::cos(rad) * trans;
        }

        if (rotatable) {
            if (Input::isKeyPress(NQ_KEY_Q))
                camRot += camRotSpeed * ts;

            if (Input::isKeyPress(NQ_KEY_E))
                camRot -= camRotSpeed * ts;

            camera.setRotation(camRot);
        }

        camera.setPosition(camPos);
        transSpeed = zoomLevel;
    }

    void OrthographicCameraController::setZoomLevel(float level)
    {
        zoomLevel = level;
        calculateView();
    }

    void OrthographicCameraController::onResize(float width, float height)
    {
        aspectRatio = width / height;
        calculateView();
    }

    void OrthographicCameraController::onEvent(Event& event)
    {
        NQ_PROFILE_FUNCTION();

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseScrollEvent>(NQ_BIND_EVENT_FN(OrthographicCameraController::onMouseScroll));
        dispatcher.dispatch<WindowResizeEvent>(NQ_BIND_EVENT_FN(OrthographicCameraController::onWindowResize));
    }

    bool OrthographicCameraController::onMouseScroll(MouseScrollEvent& e)
    {
        NQ_PROFILE_FUNCTION();

        zoomLevel -= e.getYOffset();
        zoomLevel = std::max(zoomLevel, 0.25f);
        calculateView();
        return false;
    }

    bool OrthographicCameraController::onWindowResize(WindowResizeEvent& e)
    {
        NQ_PROFILE_FUNCTION();

        onResize(static_cast<float>(e.getWidth()), static_cast<float>(e.getHeight()));
        return false;
    }

    void OrthographicCameraController::calculateView()
    {
        bounds = { -aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel };
        camera.setProjection(bounds.left, bounds.right, bounds.bottom, bounds.top);
    }



}