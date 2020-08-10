//
// Created by nauq302 on 10/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_IMGUILAYER_HPP
#define NAUQ_GAME_ENGINE_IMGUILAYER_HPP

#include "../Layer.hpp"

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
    };
}



#endif //NAUQ_GAME_ENGINE_IMGUILAYER_HPP
