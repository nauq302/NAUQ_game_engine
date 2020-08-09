//
// Created by nauq302 on 09/08/2020.
//

#include "nauq/Layer.hpp"

namespace nauq {

    /**
     *
     * @param name
     */
    Layer::Layer(std::string_view name) :
        debugName(name)
    {

    }

    /**
     *
     */
    Layer::~Layer() = default;
}