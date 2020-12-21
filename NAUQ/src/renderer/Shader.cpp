//
// Created by nauq302 on 20/12/2020.
//

#include "nauq/renderer/Shader.hpp"

#include "nauq/renderer/Renderer.hpp"
#include "nauq/platform/openGL/OpenGLShader.hpp"

namespace nauq {

    Shader* Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE: NQ_CORE_ASSERT(false, "RendererAPI::NONE is not currently supported!"); return nullptr;
            case RendererAPI::API::OPEN_GL: return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        NQ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}