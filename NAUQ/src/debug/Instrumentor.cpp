//
// Created by nauq302 on 14/04/2021.
//

#include "nauq/debug/Instrumentor.hpp"

#include <thread>

namespace nauq {

    void Instrumentor::begin(const std::string& name, const std::string& filepath)
    {
        out.open(filepath);
        writeHeader();
        currentSession = new InstrumentorSession{ name };
    }

    void Instrumentor::end()
    {
        writeFooter();
        out.close();
        delete currentSession;
        currentSession = nullptr;
        profileCount = 0;
    }

    void Instrumentor::writeProfile(const ProfileResult& result)
    {
        if (profileCount++ > 0) {
            out << ',';
        }

        std::string name = result.name;
        std::replace(name.begin(), name.end(), '"', '\'');

        out << '{'
            << R"("cat":"function",)"
            << R"("dur":)" << result.end - result.start << ','
            << R"("name":")" << name << R"(",)"
            << R"("ph":"X",)"
            << R"("pid":0,)"
            << R"("tid":)" << result.threadID << ','
            << R"("ts":)" << result.start
            << '}'
            << std::endl;
    }

    void InstrumentorTimer::stop()
    {

        auto end = std::chrono::high_resolution_clock::now();

        long long s = std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count();
        long long e = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();

        std::uint32_t threadID = std::hash<std::thread::id>()(std::this_thread::get_id());
        Instrumentor::get().writeProfile({ name, s, e, threadID });
    }
}
