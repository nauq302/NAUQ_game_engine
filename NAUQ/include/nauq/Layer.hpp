//
// Created by nauq302 on 09/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_LAYER_HPP
#define NAUQ_GAME_ENGINE_LAYER_HPP

#include "Core.hpp"
#include "events/Event.hpp"

#include <string>

namespace nauq {
    class NAUQ_API Layer
    {
    protected:
        std::string debugName;

    public:
        explicit Layer(std::string_view name = "Layer");
        virtual ~Layer();

    public:
        [[nodiscard]] inline const std::string& getName() const { return debugName; }

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onEvent(Event& event) {}
    };
}



#endif //NAUQ_GAME_ENGINE_LAYER_HPP
