//
// Created by nauq302 on 10/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_IMGUILAYER_HPP
#define NAUQ_GAME_ENGINE_IMGUILAYER_HPP

#include "nauq/Layer.hpp"

#include "nauq/events/ApplicationEvent.hpp"
#include "nauq/events/KeyEvent.hpp"
#include "nauq/events/MouseEvent.hpp"

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

        void begin();
        void end();

    private:
        static inline ImGuiIO& getIO() { return ImGui::GetIO(); }
    };
}



#endif //NAUQ_GAME_ENGINE_IMGUILAYER_HPP
