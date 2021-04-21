//
// Created by nauq302 on 20/12/2020.
//

#include "nauq/renderer/Shader.hpp"

#include "nauq/renderer/Renderer.hpp"
#include "nauq/platform/openGL/OpenGLShader.hpp"

namespace nauq {

    Ref<Shader> Shader::create(const std::string& filepath)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE: NQ_CORE_ASSERT(false, "RendererAPI::NONE is not currently supported!"); return nullptr;
            case RendererAPI::API::OPEN_GL: return createRef<OpenGLShader>(filepath);
        }

        NQ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }


    Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE: NQ_CORE_ASSERT(false, "RendererAPI::NONE is not currently supported!"); return nullptr;
            case RendererAPI::API::OPEN_GL: return createRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        NQ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }


    void ShaderLibrary::add(const Ref<Shader>& shader)
    {
        auto& name = shader->getName();
        NQ_CORE_ASSERT(!shaders.contains(name), "Shader already exists!!!");
        shaders[name] = shader;
    }

    void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader)
    {
        NQ_CORE_ASSERT(!shaders.contains(name), "Shader already exists!!!");
        shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string& filepath)
    {
        auto shader = Shader::create(filepath);
        add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath)
    {
        auto shader = Shader::create(filepath);
        add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::get(const std::string& name)
    {
        auto it = shaders.find(name);
        NQ_CORE_ASSERT(it != shaders.end(), "Shader not found!");
        return it->second;
    }


}