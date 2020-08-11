//
// Created by nauq302 on 10/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_IMGUILAYER_HPP
#define NAUQ_GAME_ENGINE_IMGUILAYER_HPP

#include "../Layer.hpp"

#include "../events/ApplicationEvent.hpp"
#include "../events/KeyEvent.hpp"
#include "../events/MouseEvent.hpp"

#include "imgui.h"

namespace nauq {

    class NAUQ_API ImGuiLayer :
            public Layer
    {
    private:
        float time;

    public:
        explicit ImGuiLayer();
        ~ImGuiLayer() override;

    public:
        void onAttach() override;
        void onDetach() override;
        void onUpdate() override;
        void onEvent(Event& event) override;

        bool onMouseButtonPress(MouseButtonPressEvent& event);
        bool onMouseButtonRelease(MouseButtonReleaseEvent& event);
        bool onMouseMove(MouseMoveEvent& event);
        bool onMouseScroll(MouseScrollEvent& event);
        bool onKeyPress(KeyPressEvent& event);
        bool onKeyRelease(KeyReleaseEvent& event);
        bool onKeyType(KeyTypeEvent& event);
        bool onWindowResize(WindowResizeEvent& event);

    private:
        inline ImGuiIO& getIO() { return ImGui::GetIO(); }
    };
}



#endif //NAUQ_GAME_ENGINE_IMGUILAYER_HPP
