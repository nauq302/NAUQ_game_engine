//
// Created by nauq302 on 20/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_OPENGLSHADER_HPP
#define NAUQ_GAME_ENGINE_OPENGLSHADER_HPP


#include <nauq/renderer/Shader.hpp>

#include <glm/glm.hpp>

namespace nauq {


    class OpenGLShader :
            public Shader
    {
    private:
        std::uint32_t rendererID;

    public:
        explicit OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader() override;

    public:
        void bind() const override;
        void unbind() const override;

        void uploadUniform(const std::string& name, int value) const;
        void uploadUniform(const std::string& name, float value) const;
        void uploadUniform(const std::string& name, const glm::vec2& value) const;
        void uploadUniform(const std::string& name, const glm::vec3& value) const;
        void uploadUniform(const std::string& name, const glm::vec4& value) const;
        void uploadUniform(const std::string& name, const glm::mat4& value) const;
    };

}



#endif //NAUQ_GAME_ENGINE_OPENGLSHADER_HPP
