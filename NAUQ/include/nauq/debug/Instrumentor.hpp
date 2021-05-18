//
// Created by nauq302 on 14/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_INSTRUMENTOR_HPP
#define NAUQ_GAME_ENGINE_INSTRUMENTOR_HPP

#include <fstream>
#include <chrono>

namespace nauq {

    struct ProfileResult
    {
        std::string name;
        long long start, end;
        uint32_t threadID;
    };

    struct InstrumentorSession
    {
        std::string name;
    };

    class Instrumentor
    {
    private:
        InstrumentorSession* currentSession;
        std::ofstream out;
        int profileCount;

    public:
        explicit inline Instrumentor() : currentSession(nullptr), profileCount(0) {}

    public:
        void begin(const std::string& name, const std::string& filepath = "results.json");
        void end();
        void writeProfile(const ProfileResult& result);
        inline void writeHeader() { out << R"({"otherData": {}, "traceEvents":[)" << std::endl; }
        inline void writeFooter() { out << "]}" << std::endl; }

        static inline Instrumentor& get() { static Instrumentor v; return v; }
    };

    class InstrumentorTimer
    {
    private:
        const char* name;
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        bool stopped;

    public:
        explicit inline InstrumentorTimer(const char* name)
            : name(name), start(std::chrono::high_resolution_clock::now()), stopped(false) {}
        inline ~InstrumentorTimer() { if (!stopped) stop(); }

    public:
        void stop();
    };
}

#define NQ_PROFILE 1

#if NQ_PROFILE
    #define NQ_PROFILE_BEGIN_SESSION(name, filepath) ::nauq::Instrumentor::get().begin(name, filepath)
    #define NQ_PROFILE_END_SESSION() ::nauq::Instrumentor::get().end()
    #define NQ_PROFILE_SCOPE(name) ::nauq::InstrumentorTimer timer##__LINE__(name);
    #define NQ_PROFILE_FUNCTION() NQ_PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
    #define NQ_PROFILE_BEGIN_SESSION(name, filepath)
    #define NQ_PROFILE_END_SESSION()
    #define NQ_PROFILE_SCOPE(name)
    #define NQ_PROFILE_FUNCTION()
#endif



#endif //NAUQ_GAME_ENGINE_INSTRUMENTOR_HPP
