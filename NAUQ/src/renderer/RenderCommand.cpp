//
// Created by nauq302 on 06/12/2020.
//

#include <nauq/renderer/OpenGLRenderAPI.hpp>
#include "nauq/renderer/RenderCommand.hpp"


namespace nauq {

    RendererAPI* RenderCommand::rendererAPI = new OpenGLRenderAPI;
}