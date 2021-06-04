//
// Created by nauq302 on 20/12/2020.
//

#include "nauq/platform/openGL/OpenGLShader.hpp"

#include "nauq/core/Log.hpp"



#include <fstream>
#include <nauq/debug/Instrumentor.hpp>

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
        NQ_PROFILE_FUNCTION();

        std::string source = readfile(filepath);
        SrcMap shaderSources = preprocess(source);
        compile(shaderSources);

        size_t lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

        size_t lastDot = filepath.rfind('.');
        size_t count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        _name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(std::string name, const std::string& vertexSrc, const std::string& fragmentSrc) :
            _name(std::move(name))
    {
        NQ_PROFILE_FUNCTION();

        SrcMap sources = {
            { GL_VERTEX_SHADER, vertexSrc},
            { GL_FRAGMENT_SHADER, fragmentSrc }
        };

        compile(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
        NQ_PROFILE_FUNCTION();

        glDeleteProgram(rendererID);
    }

    void OpenGLShader::bind() const
    {
        NQ_PROFILE_FUNCTION();

        glUseProgram(rendererID);
    }

    void OpenGLShader::unbind() const
    {
        NQ_PROFILE_FUNCTION();

        glUseProgram(0);
    }

    void OpenGLShader::set(const std::string& name, int value)
    {
        NQ_PROFILE_FUNCTION();
        uploadUniform(name, value);
    }

    void OpenGLShader::set(const std::string& name, float value)
    {
        NQ_PROFILE_FUNCTION();
        uploadUniform(name, value);
    }

    void OpenGLShader::set(const std::string& name, std::span<int> value)
    {
        NQ_PROFILE_FUNCTION();
        uploadUniform(name, value);
    }

    void OpenGLShader::set(const std::string& name, const glm::vec3& value)
    {
        NQ_PROFILE_FUNCTION();
        uploadUniform(name, value);
    }

    void OpenGLShader::set(const std::string& name, const glm::vec4& value)
    {
        NQ_PROFILE_FUNCTION();
        uploadUniform(name, value);
    }

    void OpenGLShader::set(const std::string& name, const glm::mat4& value)
    {
        NQ_PROFILE_FUNCTION();
        uploadUniform(name, value);
    }

    std::string OpenGLShader::readfile(const std::string& filepath)
    {
        NQ_PROFILE_FUNCTION();

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
        NQ_PROFILE_FUNCTION();

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
        NQ_PROFILE_FUNCTION();

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


    int OpenGLShader::getLocation(const std::string& uname) const
    {
        auto it = locations.find(uname);

        if (it != locations.end()) {
            return it->second;
        }

        int location = glGetUniformLocation(rendererID, uname.c_str());

        if (location == -1) {
            NQ_CORE_WARN("{0} not found!!!!", uname);
        } else {
            locations.insert({ uname, location });
        }

        return location;
    }


}