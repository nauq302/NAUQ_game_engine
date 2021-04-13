//
// Created by nauq302 on 22/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_TEXTURE_HPP
#define NAUQ_GAME_ENGINE_TEXTURE_HPP

#include "nauq/Core.hpp"

namespace nauq {

    class Texture
    {
    public:
        virtual ~Texture() = default;

    public:
        [[nodiscard]] virtual std::uint32_t getWidth() const = 0;
        [[nodiscard]] virtual std::uint32_t getHeight() const = 0;

        virtual void setData(void* data, std::size_t size) = 0;

        virtual void bind(std::uint32_t slot = 0) const = 0;
        virtual void unbind() const = 0;
    };

    class Texture2D :
            public Texture
    {
    public:
        static Ref<Texture2D> create(std::uint32_t width, std::uint32_t height);
        static Ref<Texture2D> create(const std::string& path);
    };

}



#endif //NAUQ_GAME_ENGINE_TEXTURE_HPP
