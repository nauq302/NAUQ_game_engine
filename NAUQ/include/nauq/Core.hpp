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

#else
    #define NAUQ_API
#endif


#ifdef NAUQ_ENABLE_ASSERTS
    #define NAUQ_ASSERT(x,...) { if (!(x)) { NAUQ_ERROR("Assert Failed: {0}", __VA_ARGS__); std::exit(1); } }
    #define NAUQ_CORE_ASSERT(x,...) { if (!(x)) { NAUQ_CORE_ERROR("Assert Failed: {0}", __VA_ARGS__); std::exit(1); } }
#else
    #define NAUQ_ASSERT(x,...)
    #define NAUQ_CORE_ASSERT(x,...)
#endif

#define NAUQ_BIND_EVENT_FN(fn) std::bind_front(&fn, this)

namespace nauq {
    /**
     *
     * @param c
     * @return
     */
    constexpr unsigned char bit(unsigned char index) { return 1u << index; }
}


#endif //NAUQ_GAME_ENGINE_CORE_HPP
