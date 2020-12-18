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


#ifdef NQ_ENABLE_ASSERTS
    #define NQ_ASSERT(x,...) !(x) ? (NQ_ERROR("Assert Failed: {0}", __VA_ARGS__), std::exit(1)) : (void)0
    #define NQ_CORE_ASSERT(x,...) !(x) ? (NQ_CORE_ERROR("Assert Failed: {0}", __VA_ARGS__), std::exit(1)) : (void)0
#else
    #define NQ_ASSERT(x,...)
    #define NQ_CORE_ASSERT(x,...)
#endif

#define NQ_BIND_EVENT_FN(fn) std::bind_front(&fn, this)

namespace nauq {
    /**
     *
     * @param c
     * @return
     */
    constexpr unsigned char bit(unsigned char index) { return 1u << index; }
}


#endif //NAUQ_GAME_ENGINE_CORE_HPP
