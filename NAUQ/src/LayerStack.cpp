//
// Created by nauq302 on 09/08/2020.
//

#include "nauq/LayerStack.hpp"

namespace nauq {

    /**
     *
     */
    LayerStack::LayerStack() : layerInsertIt(layers.begin()) {}

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
        layerInsertIt = layers.emplace(layerInsertIt, layer);
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
            --layerInsertIt;
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


