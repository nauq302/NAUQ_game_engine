//
// Created by nauq302 on 22/12/2020.
//

#include "nauq/renderer/Texture.hpp"

#include "nauq/renderer/Renderer.hpp"
#include "nauq/platform/openGL/OpenGLTexture.hpp"

#include <memory>

namespace nauq {

    Ref<Texture2D> Texture2D::create(std::uint32_t width, std::uint32_t height)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE:    NQ_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported");
            case RendererAPI::API::OPEN_GL: return createRef<OpenGLTexture2D>(width, height);
        }

        NQ_CORE_ASSERT(false, "Unknown RenderedAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::create(const std::string& path)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::NONE:    NQ_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported");
            case RendererAPI::API::OPEN_GL: return createRef<OpenGLTexture2D>(path);
        }

        NQ_CORE_ASSERT(false, "Unknown RenderedAPI!");
        return nullptr;
    }


}