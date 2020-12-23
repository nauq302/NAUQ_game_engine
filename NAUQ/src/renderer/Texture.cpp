//
// Created by nauq302 on 22/12/2020.
//

#include "nauq/renderer/Texture.hpp"

#include "nauq/renderer/Renderer.hpp"
#include "nauq/platform/openGL/OpenGLTexture.hpp"

#include <memory>

namespace nauq {

    Ref<Texture2D> Texture2D::create(const std::string& path)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE:    NQ_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported");
            case RendererAPI::API::OPEN_GL: return std::make_shared<OpenGLTexture2D>(path);
        }

        NQ_CORE_ASSERT(false, "Unknown RenderedAPI!");
        return nullptr;
    }
}