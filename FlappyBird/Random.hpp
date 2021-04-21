//
// Created by nauq302 on 16/04/2021.
//

#ifndef NAUQ_GAME_ENGINE_RANDOM_HPP
#define NAUQ_GAME_ENGINE_RANDOM_HPP

#include <random>

class Random
{
private:
    static std::mt19937 randomEngine;
    static std::uniform_int_distribution<std::mt19937::result_type> distribution;

public:
    static inline void init() { randomEngine.seed(std::random_device()()); }
    static inline float getFloat() {
        return static_cast<float>(distribution(randomEngine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
    }

};


#endif //NAUQ_GAME_ENGINE_RANDOM_HPP
