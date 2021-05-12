//
// Created by nauq302 on 07/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_OPENGLFRAMEBUFFER_HPP
#define NAUQ_GAME_ENGINE_OPENGLFRAMEBUFFER_HPP

#include "nauq/renderer/Framebuffer.hpp"

namespace nauq {

    class OpenGLFramebuffer :
            public Framebuffer
    {
    private:
        uint32_t rendererID = 0;
        uint32_t colorAttachment = 0;
        uint32_t depthAttachment = 0;
        FramebufferSpecification spec;

    public:
        explicit OpenGLFramebuffer(const FramebufferSpecification& spec);
        ~OpenGLFramebuffer() override;

    public:
        [[nodiscard]] const FramebufferSpecification& getSpecification() const override { return spec; }
        [[nodiscard]] uint32_t getColorAttachment() const override { return colorAttachment; }

        void bind() override;
        void unbind() override;


        void resize(uint32_t width, uint32_t height) override;

        void invalidate();
    };
}




#endif //NAUQ_GAME_ENGINE_OPENGLFRAMEBUFFER_HPP
