//
// Created by nauq302 on 19/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_SCRIPTABLEENTITY_HPP
#define NAUQ_GAME_ENGINE_SCRIPTABLEENTITY_HPP

#include "Entity.hpp"

namespace nauq {

    class ScriptableEntity
    {
        friend class Scene;
    private:
        Entity entity;

    public:
        template<ComponentType C>
        C& get() { return entity.template get<C>(); }

    protected:
        virtual void onCreate() {};
        virtual void onDestroy() {};
        virtual void onUpdate(TimeStep ts) {};

    };


}


#endif //NAUQ_GAME_ENGINE_SCRIPTABLEENTITY_HPP
