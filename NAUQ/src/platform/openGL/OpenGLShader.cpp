//
// Created by nauq302 on 20/12/2020.
//

#include "nauq/platform/openGL/OpenGLShader.hpp"

#include "nauq/Log.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace nauq {


    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* source = vertexSrc.c_str();

        glShaderSource(vertexShader, 1, &source, nullptr);
        glCompileShader(vertexShader);

        GLint isCompiled;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE) {
            GLint maxLen = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLen);

            char infoLog[maxLen];
            glGetShaderInfoLog(vertexShader, maxLen, &maxLen, infoLog);

            glDeleteShader(vertexShader);

            NQ_CORE_ERROR("{0}", static_cast<const char*>(infoLog));
            NQ_CORE_ASSERT(false, "Vertex Shader compilation failed");
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        source = fragmentSrc.c_str();

        glShaderSource(fragmentShader, 1, &source, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE) {
            GLint maxLen = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLen);

            char infoLog[maxLen];
            glGetShaderInfoLog(fragmentShader, maxLen, &maxLen, infoLog);

            glDeleteShader(fragmentShader);
            std::cout << "f" <<'\n';
            NQ_CORE_ERROR("{0}", static_cast<const char*>(infoLog));
            NQ_CORE_ASSERT(false, "Fragment Shader compilation failed");
        }

        rendererID = glCreateProgram();

        glAttachShader(rendererID, vertexShader);
        glAttachShader(rendererID, fragmentShader);

        glLinkProgram(rendererID);

        GLint isLinked;
        glGetProgramiv(rendererID, GL_LINK_STATUS, &isLinked);

        if (isLinked == GL_FALSE) {
            int maxLen;
            glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLen);

            char infoLog[maxLen];
            glGetProgramInfoLog(rendererID, maxLen, &maxLen, infoLog);

            glDeleteProgram(rendererID);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            NQ_CORE_ERROR("{0}", static_cast<const char*>(infoLog));
            NQ_CORE_ASSERT(false, "Shader link failed");
        }

        glDetachShader(rendererID, vertexShader);
        glDetachShader(rendererID, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(rendererID);
    }

    void OpenGLShader::bind() const
    {
        glUseProgram(rendererID);
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::uploadUniform(const std::string &name, int value) const
    {
        int location = glGetUniformLocation(rendererID, name.c_str());
        glUniform1i(location, value);
    }
    void OpenGLShader::uploadUniform(const std::string &name, float value) const
    {
        int location = glGetUniformLocation(rendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::uploadUniform(const std::string &name, const glm::vec2& value) const
    {
        int location = glGetUniformLocation(rendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::uploadUniform(const std::string &name, const glm::vec3& value) const
    {
        int location = glGetUniformLocation(rendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }


    void OpenGLShader::uploadUniform(const std::string &name, const glm::vec4& value) const
    {
        int location = glGetUniformLocation(rendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::uploadUniform(const std::string& name, const glm::mat4& value) const
    {
        int location = glGetUniformLocation(rendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
}