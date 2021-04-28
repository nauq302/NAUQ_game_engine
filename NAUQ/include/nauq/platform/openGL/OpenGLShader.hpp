//
// Created by nauq302 on 20/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_OPENGLSHADER_HPP
#define NAUQ_GAME_ENGINE_OPENGLSHADER_HPP


#include <nauq/renderer/Shader.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace nauq {


    class OpenGLShader :
            public Shader
    {
    private:
        using SrcMap = std::unordered_map<GLenum, std::string>;
        using Locations = std::unordered_map<std::string, int>;

        mutable Locations locations;
        std::uint32_t rendererID = 0;
        std::string _name;

    public:
        explicit OpenGLShader(const std::string& filepath);
        explicit OpenGLShader(std::string name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader() override;

    public:
        void bind() const override;
        void unbind() const override;

        [[nodiscard]] const std::string& getName() const override { return _name; }

        void set(const std::string& name, int value) override;
        void set(const std::string& name, float value) override;
        void set(const std::string& name, std::span<int> value) override;
        void set(const std::string& name, const glm::vec3& value) override;
        void set(const std::string& name, const glm::vec4& value) override;
        void set(const std::string& name, const glm::mat4& value) override;

        inline void uploadUniform(const std::string& uname, int value) const;
        inline void uploadUniform(const std::string& uname, float value) const;
        inline void uploadUniform(const std::string& name, std::span<int> value) const;
        inline void uploadUniform(const std::string& uname, const glm::vec2& value) const;
        inline void uploadUniform(const std::string& uname, const glm::vec3& value) const;
        inline void uploadUniform(const std::string& uname, const glm::vec4& value) const;
        inline void uploadUniform(const std::string& uname, const glm::mat4& value) const;

    private:
        static std::string readfile(const std::string& filepath);
        static SrcMap preprocess(const std::string& source);
        void compile(const SrcMap& shaderSources);
        [[nodiscard]] int getLocation(const std::string& uname) const;

    };


    void OpenGLShader::uploadUniform(const std::string& uname, int value) const
    {
        glUniform1i(getLocation(uname), value);
    }
    void OpenGLShader::uploadUniform(const std::string& uname, float value) const
    {
        glUniform1f(getLocation(uname), value);
    }

    void OpenGLShader::uploadUniform(const std::string& uname, std::span<int> value) const
    {
        glUniform1iv(getLocation(uname), value.size(), value.data());
    }

    void OpenGLShader::uploadUniform(const std::string& uname, const glm::vec2& value) const
    {
        glUniform2f(getLocation(uname), value.x, value.y);
    }

    void OpenGLShader::uploadUniform(const std::string& uname, const glm::vec3& value) const
    {
        glUniform3f(getLocation(uname), value.x, value.y, value.z);
    }

    void OpenGLShader::uploadUniform(const std::string& uname, const glm::vec4& value) const
    {
        glUniform4f(getLocation(uname), value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::uploadUniform(const std::string& uname, const glm::mat4& value) const
    {
        glUniformMatrix4fv(getLocation(uname), 1, GL_FALSE, glm::value_ptr(value));
    }

}



#endif //NAUQ_GAME_ENGINE_OPENGLSHADER_HPP
