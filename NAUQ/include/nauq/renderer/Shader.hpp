//
// Created by nauq302 on 12/10/2020.
//

#ifndef NAUQ_GAME_ENGINE_SHADER_HPP
#define NAUQ_GAME_ENGINE_SHADER_HPP

#include <string>

namespace nauq {


    class Shader
    {
    private:
        std::uint32_t rendererID;

    public:
        explicit Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind() const;
        void unbind() const;
    };

}


#endif //NAUQ_GAME_ENGINE_SHADER_HPP
