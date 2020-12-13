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
    private:
        std::uint32_t rendererID;

    public:
        explicit Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

    public:
        void bind() const;
        void unbind() const;

        void uploadUniform(const std::string& name, const glm::mat4& matrix);
    };

}


#endif //NAUQ_GAME_ENGINE_SHADER_HPP
