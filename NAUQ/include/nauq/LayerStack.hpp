//
// Created by nauq302 on 09/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_LAYERSTACK_HPP
#define NAUQ_GAME_ENGINE_LAYERSTACK_HPP

#include "Layer.hpp"

#include <list>

namespace nauq {

    /**
     *
     */
    class NAUQ_API LayerStack
    {
    public:
        using Container = std::list<Layer*>;
        using Iterator = Container::iterator;
        using ReverseIterator = Container::reverse_iterator;

    private:
        Container layers;
        Iterator layerInsertIt;

    public:
        explicit LayerStack();
        ~LayerStack();

    public:
        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
        void popLayer(Layer* layer);
        void popOverlay(Layer* overlay);

        inline Iterator begin() { return layers.begin(); }
        inline Iterator end() { return layers.end(); }
        inline ReverseIterator rbegin() { return layers.rbegin(); }
        inline ReverseIterator rend() { return layers.rend(); }
    };
}




#endif //NAUQ_GAME_ENGINE_LAYERSTACK_HPP
