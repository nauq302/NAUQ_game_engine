//
// Created by nauq302 on 12/10/2020.
//

#include "nauq/Log.hpp"
#include "nauq/renderer/Shader.hpp"


namespace nauq {


    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
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

            NAUQ_CORE_ERROR("{0}", static_cast<const char*>(infoLog));
            NAUQ_CORE_ASSERT(false, "Vertex Shader compilation failed");
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
            NAUQ_CORE_ERROR("{0}", static_cast<const char*>(infoLog));
            NAUQ_CORE_ASSERT(false, "Fragment Shader compilation failed");
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

            NAUQ_CORE_ERROR("{0}", static_cast<const char*>(infoLog));
            NAUQ_CORE_ASSERT(false, "Shader link failed");
        }

        glDetachShader(rendererID, vertexShader);
        glDetachShader(rendererID, fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(rendererID);
    }

    void Shader::bind() const
    {
        glUseProgram(rendererID);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }
}