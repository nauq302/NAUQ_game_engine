//
// Created by nauq302 on 15/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_TIMESTEP_HPP
#define NAUQ_GAME_ENGINE_TIMESTEP_HPP

namespace nauq {

    class TimeStep
    {
    private:
        float time;

    public:
        inline TimeStep(float sec = 0.f) : time(sec) {}

    public:
        inline operator float&() { return time; }
        [[nodiscard]] inline float getSeconds() const { return time; }
        [[nodiscard]] inline float getMilliseconds() const { return time * 1000.f; }
    };
}




#endif //NAUQ_GAME_ENGINE_TIMESTEP_HPP
