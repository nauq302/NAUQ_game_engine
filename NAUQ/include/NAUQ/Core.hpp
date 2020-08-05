//
// Created by nauq302 on 05/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_CORE_HPP
#define NAUQ_GAME_ENGINE_CORE_HPP

#ifdef NAUQ_PLATFORM_WINDOWS
    #ifdef NAUQ_BUILD_DLL
        #define NAUQ_API __declspec(dllexport)
    #else
        #define NAUQ_API __declspec(dllimport)
    #endif

#endif
    #define NAUQ_API

#endif //NAUQ_GAME_ENGINE_CORE_HPP
