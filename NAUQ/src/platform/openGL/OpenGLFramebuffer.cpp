//
// Created by nauq302 on 07/05/2021.
//

#include "nauq/platform/openGL/OpenGLFramebuffer.hpp"
#include "nauq/Log.hpp"

#include <glad/glad.h>

namespace nauq {

    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec) :
            spec(spec)
    {
        invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &rendererID);
        glDeleteTextures(1, &colorAttachment);
        glDeleteTextures(1, &depthAttachment);
    }

    void OpenGLFramebuffer::invalidate()
    {
        if (rendererID) {
            glDeleteFramebuffers(1, &rendererID);
            glDeleteTextures(1, &colorAttachment);
            glDeleteTextures(1, &depthAttachment);
        }

        glCreateFramebuffers(1, &rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, rendererID);

        glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment);
        glBindTexture(GL_TEXTURE_2D, colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachment);
        glBindTexture(GL_TEXTURE_2D, depthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, spec.width, spec.height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachment, 0);

        NQ_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");


        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, rendererID);
        glViewport(0, 0, spec.width, spec.height);
    }

    void OpenGLFramebuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::resize(uint32_t width, uint32_t height)
    {
        spec.width = width;
        spec.height = height;
        invalidate();
    }
}