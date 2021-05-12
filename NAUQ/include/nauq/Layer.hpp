//
// Created by nauq302 on 09/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_LAYER_HPP
#define NAUQ_GAME_ENGINE_LAYER_HPP

#include "nauq/core/Core.hpp"
#include "events/Event.hpp"

#include <string>
#include <nauq/core/TimeStep.hpp>

namespace nauq {
    class NAUQ_API Layer
    {
    protected:
        std::string debugName;

    public:
        explicit Layer(std::string_view name = "Layer") : debugName(name) {}
        virtual ~Layer() = default;

    public:
        [[nodiscard]] inline const std::string& getName() const { return debugName; }

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(TimeStep ts) {}
        virtual void onImGuiRender() {}
        virtual void onEvent(Event& event) {}
    };
}



#endif //NAUQ_GAME_ENGINE_LAYER_HPP
