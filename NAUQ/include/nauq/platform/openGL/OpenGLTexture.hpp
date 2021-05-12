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
        uint32_t rendererID;
        uint32_t width;
        uint32_t height;
        GLenum internalFormat;
        GLenum dataFormat;


    public:
        explicit OpenGLTexture2D(uint32_t width, uint32_t height);
        explicit OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;

    public:
        [[nodiscard]] uint32_t getWidth() const override { return width; }
        [[nodiscard]] uint32_t getHeight() const override { return height; }
        [[nodiscard]] uint32_t getRendererID() const override { return rendererID; }

        void setData(void* data, std::size_t size) override;

        void bind(uint32_t slot = 0) const override;
        void unbind() const override;

        bool operator ==(const Texture& other) const override
        {
            auto* p = dynamic_cast<const OpenGLTexture2D*>(&other);
            return p == nullptr ? false : rendererID == p->rendererID;
        }
    };
}



#endif //NAUQ_GAME_ENGINE_OPENGLTEXTURE_HPP
