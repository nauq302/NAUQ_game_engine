//
// Created by nauq302 on 20/12/2020.
//

#include "nauq/platform/openGL/OpenGLShader.hpp"

#include "nauq/Log.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>

namespace nauq {

    static GLenum shaderTypeOf(const std::string& type)
    {
        if (type == "vertex") return GL_VERTEX_SHADER;
        if (type == "fragment") return GL_FRAGMENT_SHADER;

        NQ_CORE_ASSERT(false, "Unknown shader type");
        return GL_NONE;
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        std::string source = readfile(filepath);
        SrcMap shaderSources = preprocess(source);
        compile(shaderSources);

        std::size_t lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

        std::size_t lastDot = filepath.rfind('.');
        std::size_t count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(std::string name, const std::string& vertexSrc, const std::string& fragmentSrc) :
        name(std::move(name))
    {
        SrcMap sources = {
            { GL_VERTEX_SHADER, vertexSrc},
            { GL_FRAGMENT_SHADER, fragmentSrc }
        };

        compile(sources);
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

    void OpenGLShader::uploadUniform(const std::string& uname, int value) const
    {
        int location = glGetUniformLocation(rendererID, uname.c_str());
        glUniform1i(location, value);
    }
    void OpenGLShader::uploadUniform(const std::string& uname, float value) const
    {
        int location = glGetUniformLocation(rendererID, uname.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::uploadUniform(const std::string& uname, const glm::vec2& value) const
    {
        int location = glGetUniformLocation(rendererID, uname.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::uploadUniform(const std::string& uname, const glm::vec3& value) const
    {
        int location = glGetUniformLocation(rendererID, uname.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }


    void OpenGLShader::uploadUniform(const std::string& uname, const glm::vec4& value) const
    {
        int location = glGetUniformLocation(rendererID, uname.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::uploadUniform(const std::string& uname, const glm::mat4& value) const
    {
        int location = glGetUniformLocation(rendererID, uname.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    std::string OpenGLShader::readfile(const std::string& filepath)
    {
        std::string result;
        std::ifstream ifs(filepath, std::ios::in | std::ios::binary);

        if (ifs) {
            ifs.seekg(0, std::ios::end);
            result.resize(ifs.tellg());

            ifs.seekg(0, std::ios::beg);
            ifs.read(result.data(), result.size());
            ifs.close();

        } else {
            NQ_CORE_ERROR("Could not open file '{0}'", filepath);
        }

        return result;
    }

    OpenGLShader::SrcMap OpenGLShader::preprocess(const std::string& source)
    {
        SrcMap shaderSources;

        char typeToken[] = "#type";
        std::size_t typeTokenLen = sizeof(typeToken) - 1;
        std::size_t pos = source.find(typeToken);

#if defined(__GNUC__)
        char endline[] = "\n";
#elif defined(__MSC_VER_)
        char endline[] = "\r\n";
#else
    #error "Not support"
#endif

        while (pos != std::string::npos) {
            std::size_t eol = source.find_first_of(endline, pos);
            NQ_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            std::size_t begin = pos + typeTokenLen + 1;
            std::string type = source.substr(begin, eol - begin);
            GLenum t = shaderTypeOf(type);
            NQ_CORE_ASSERT(t != GL_NONE, "Invalid shader type specified");

            std::size_t nextLinePos = source.find_first_not_of(endline, eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[t] = source.substr(nextLinePos,
                    pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos)
            );
        }

        return shaderSources;
    }

    void OpenGLShader::compile(const OpenGLShader::SrcMap& shaderSources)
    {
        GLuint program = glCreateProgram();

        NQ_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
        std::array<GLenum, 2> shaderIDs = { 0, };
        std::size_t count = 0;

        for (auto&[type, source] : shaderSources) {
            GLuint shader = glCreateShader(type);
            const char* src = source.c_str();

            glShaderSource(shader, 1, &src, nullptr);
            glCompileShader(shader);

            GLint isCompiled;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

            if (isCompiled == GL_FALSE) {
                GLint maxLen = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLen);

                std::vector<char> infoLog(maxLen);
                glGetShaderInfoLog(shader, maxLen, &maxLen, infoLog.data());

                glDeleteShader(shader);

                NQ_CORE_ERROR("{0}", infoLog.data());
                NQ_CORE_ASSERT(false, "Shader compilation failed");
            }

            glAttachShader(program, shader);
            shaderIDs[count++] = shader;
        }

        rendererID = program;

        glLinkProgram(rendererID);

        GLint isLinked;
        glGetProgramiv(rendererID, GL_LINK_STATUS, &isLinked);

        if (isLinked == GL_FALSE) {
            int maxLen;
            glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLen);

            std::vector<char> infoLog(maxLen);
            glGetProgramInfoLog(rendererID, maxLen, &maxLen, infoLog.data());

            glDeleteProgram(rendererID);
            for (GLenum id :shaderIDs) {
                glDeleteShader(id);
            }

            NQ_CORE_ERROR("{0}", infoLog.data());
            NQ_CORE_ASSERT(false, "Shader link failed");
        }

        for (GLenum id : shaderIDs) {
            glDetachShader(rendererID, id);
        }
    }


}