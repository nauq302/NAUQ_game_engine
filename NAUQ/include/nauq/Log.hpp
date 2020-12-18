//
// Created by nauq302 on 06/08/2020.
//

#ifndef NAUQ_GAME_ENGINE_LOG_HPP
#define NAUQ_GAME_ENGINE_LOG_HPP

#include "Core.hpp"

#include "spdlog/spdlog.h"


namespace nauq {

    /**
     *
     */
    class NAUQ_API Log
    {
    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;

    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
        inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }
    };
}

// Core Log macros
#define NQ_CORE_TRACE(...) ::nauq::Log::getCoreLogger()->trace(__VA_ARGS__)
#define NQ_CORE_INFO(...) ::nauq::Log::getCoreLogger()->info(__VA_ARGS__)
#define NQ_CORE_WARN(...) ::nauq::Log::getCoreLogger()->warn(__VA_ARGS__)
#define NQ_CORE_ERROR(...) ::nauq::Log::getCoreLogger()->error(__VA_ARGS__)
#define NQ_CORE_FATAL(...) ::nauq::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros
#define NQ_TRACE(...) ::nauq::Log::getClientLogger()->trace(__VA_ARGS__)
#define NQ_INFO(...) ::nauq::Log::getClientLogger()->info(__VA_ARGS__)
#define NQ_WARN(...) ::nauq::Log::getClientLogger()->warn(__VA_ARGS__)
#define NQ_ERROR(...) ::nauq::Log::getClientLogger()->error(__VA_ARGS__)
#define NQ_FATAL(...) ::nauq::Log::getClientLogger()->fatal(__VA_ARGS__)



#endif //NAUQ_GAME_ENGINE_LOG_HPP
