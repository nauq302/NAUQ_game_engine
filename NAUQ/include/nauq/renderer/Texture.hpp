//
// Created by nauq302 on 22/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_TEXTURE_HPP
#define NAUQ_GAME_ENGINE_TEXTURE_HPP

#include "nauq/core/Core.hpp"

namespace nauq {

    class Texture
    {
    public:
        virtual ~Texture() = default;

    public:
        [[nodiscard]] virtual uint32_t getWidth() const = 0;
        [[nodiscard]] virtual uint32_t getHeight() const = 0;
        [[nodiscard]] virtual uint32_t getRendererID() const = 0;

        virtual void setData(void* data, size_t size) = 0;

        virtual void bind(uint32_t slot = 0) const = 0;
        virtual void unbind() const = 0;

        virtual bool operator ==(const Texture& other) const = 0;
    };

    class Texture2D :
            public Texture
    {
    public:
        static Ref<Texture2D> create(uint32_t width, uint32_t height);
        static Ref<Texture2D> create(const std::string& path);
    };

}



#endif //NAUQ_GAME_ENGINE_TEXTURE_HPP
