//
// Created by nauq302 on 05/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_CORE_HPP
#define NAUQ_GAME_ENGINE_CORE_HPP

#include <memory>

#ifdef NAUQ_PLATFORM_WINDOWS
    #ifdef NAUQ_BUILD_DLL
        #define NAUQ_API __declspec(dllexport)
    #else
        #define NAUQ_API __declspec(dllimport)
    #endif

    #define NQ_DEBUG_BREAK() __debugbreak()

#else
    #define NAUQ_API
    #define NQ_DEBUG_BREAK() __builtin_trap()
    #include <csignal>
#endif


#ifdef NQ_ENABLE_ASSERTS
    #define NQ_ASSERT(x,...) !(x) ? (NQ_ERROR("Assert Failed: {0}", __VA_ARGS__), NQ_DEBUG_BREAK()) : (void)0
    #define NQ_CORE_ASSERT(x,...) !(x) ? (NQ_CORE_ERROR("Assert Failed: {0}", __VA_ARGS__), NQ_DEBUG_BREAK()) : (void)0
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

    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T, typename... Ts>
    constexpr Ref<T> createRef(Ts&&... ts) { return std::make_shared<T>(std::forward<Ts>(ts)...); }

    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T, typename... Ts>
    constexpr Scope<T> createScope(Ts&&... ts) { return std::make_unique<T>(std::forward<Ts>(ts)...); }
}


#endif //NAUQ_GAME_ENGINE_CORE_HPP
