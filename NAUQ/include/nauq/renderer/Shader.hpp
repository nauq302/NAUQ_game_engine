//
// Created by nauq302 on 12/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_SHADER_HPP
#define NAUQ_GAME_ENGINE_SHADER_HPP

#include <glm/glm.hpp>

#include <string>

namespace nauq {


    class Shader
    {
    public:
        virtual ~Shader() = default;

    public:
        static Shader* create(const std::string& vertexSrc, const std::string& fragmentSrc);

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
    };

}


#endif //NAUQ_GAME_ENGINE_SHADER_HPP
