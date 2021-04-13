//
// Created by nauq302 on 22/12/2020.
//

#ifndef NAUQ_GAME_ENGINE_OPENGLTEXTURE_HPP
#define NAUQ_GAME_ENGINE_OPENGLTEXTURE_HPP

#include "nauq/renderer/Texture.hpp"

namespace nauq {

    class OpenGLTexture2D :
            public Texture2D
    {
    private:
        std::string path;
        std::uint32_t rendererID;
        std::uint32_t width;
        std::uint32_t height;
        GLenum internalFormat;
        GLenum dataFormat;


    public:
        explicit OpenGLTexture2D(std::uint32_t width, std::uint32_t height);
        explicit OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;

    public:
        [[nodiscard]] std::uint32_t getWidth() const override { return width; }
        [[nodiscard]] std::uint32_t getHeight() const override { return height; }

        void setData(void* data, std::size_t size) override;

        void bind(std::uint32_t slot = 0) const override;
        void unbind() const override;
    };
}



#endif //NAUQ_GAME_ENGINE_OPENGLTEXTURE_HPP
