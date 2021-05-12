//
// Created by nauq302 on 07/05/2021.
//

#ifndef NAUQ_GAME_ENGINE_FRAMEBUFFER_HPP
#define NAUQ_GAME_ENGINE_FRAMEBUFFER_HPP

#include "nauq/core/Core.hpp"

namespace nauq {

    struct FramebufferSpecification
    {
        uint32_t width, height;
        uint32_t samples = 1;
        bool swapChainTarget = false;
    };

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;

    public:
        static Ref<Framebuffer> create(const FramebufferSpecification& spec);

        [[nodiscard]] virtual const FramebufferSpecification& getSpecification() const = 0;
        [[nodiscard]] virtual uint32_t getColorAttachment() const = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void resize(uint32_t width, uint32_t height) = 0;
    };

}




#endif //NAUQ_GAME_ENGINE_FRAMEBUFFER_HPP
