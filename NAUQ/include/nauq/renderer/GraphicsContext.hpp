//
// Created by nauq302 on 06/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_GRAPHICSCONTEXT_HPP
#define NAUQ_GAME_ENGINE_GRAPHICSCONTEXT_HPP

namespace nauq {

    class GraphicsContext
    {
    public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };

}



#endif //NAUQ_GAME_ENGINE_GRAPHICSCONTEXT_HPP
