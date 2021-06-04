//
// Created by nauq302 on 09/08/2020.
//

#include "nauq/core/LayerStack.hpp"

namespace nauq {

    /**
     *
     */
    LayerStack::LayerStack() : layerInsertIndex(0) {}

    /**
     *
     */
    LayerStack::~LayerStack()
    {
        for (Layer* l : layers) {
            delete l;
        }
    }

    /**
     *
     * @param layer
     */
    void LayerStack::pushLayer(Layer* layer)
    {
        layers.emplace(layers.begin() + layerInsertIndex, layer);
        ++layerInsertIndex;
    }

    /**
     *
     * @param overlay
     */
    void LayerStack::pushOverlay(Layer* overlay)
    {
        layers.emplace_back(overlay);
    }

    /**
     *
     * @param layer
     */
    void LayerStack::popLayer(Layer* layer)
    {
        auto it = std::find(layers.begin(), layers.end(), layer);

        if (it != layers.end()) {
            layers.erase(it);
            --layerInsertIndex;
        }
    }

    /**
     *
     * @param overlay
     */
    void LayerStack::popOverlay(Layer* overlay)
    {
        auto it = std::find(layers.begin(), layers.end(), overlay);

        if (it != layers.end()) {
            layers.erase(it);
        }
    }


}


