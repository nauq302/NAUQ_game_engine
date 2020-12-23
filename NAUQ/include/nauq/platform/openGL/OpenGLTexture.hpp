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


    public:
        explicit OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;

    public:
        [[nodiscard]] std::uint32_t getWidth() const override { return width; }

        [[nodiscard]] std::uint32_t getHeight() const override { return height; }

        virtual void bind(std::uint32_t slot = 0) const override;
    };
}



#endif //NAUQ_GAME_ENGINE_OPENGLTEXTURE_HPP
