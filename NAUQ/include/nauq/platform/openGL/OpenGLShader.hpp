//
// Created by nauq302 on 20/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_OPENGLSHADER_HPP
#define NAUQ_GAME_ENGINE_OPENGLSHADER_HPP


#include <nauq/renderer/Shader.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace nauq {


    class OpenGLShader :
            public Shader
    {
    private:
        using SrcMap = std::unordered_map<GLenum, std::string>;
        std::uint32_t rendererID = 0;
        std::string name;

    public:
        explicit OpenGLShader(const std::string& filepath);
        explicit OpenGLShader(std::string name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader() override;

    public:
        void bind() const override;
        void unbind() const override;

        [[nodiscard]] const std::string& getName() const override { return name; }

        void uploadUniform(const std::string& uname, int value) const;
        void uploadUniform(const std::string& uname, float value) const;
        void uploadUniform(const std::string& uname, const glm::vec2& value) const;
        void uploadUniform(const std::string& uname, const glm::vec3& value) const;
        void uploadUniform(const std::string& uname, const glm::vec4& value) const;
        void uploadUniform(const std::string& uname, const glm::mat4& value) const;

    private:
        static std::string readfile(const std::string& filepath);
        SrcMap preprocess(const std::string& source);
        void compile(const SrcMap& shaderSources);

    };

}



#endif //NAUQ_GAME_ENGINE_OPENGLSHADER_HPP
