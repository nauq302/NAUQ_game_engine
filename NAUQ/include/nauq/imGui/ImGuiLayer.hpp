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
        void onImGuiRender() override;

        void begin();
        void end();

    private:
        static inline ImGuiIO& getIO() { return ImGui::GetIO(); }
    };
}



#endif //NAUQ_GAME_ENGINE_IMGUILAYER_HPP
