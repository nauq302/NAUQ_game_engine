//
// Created by nauq302 on 22/12/2020.
//

#include "nauq/platform/openGL/OpenGLTexture.hpp"

#include "nauq/Log.hpp"
#include "stb_image.hpp"


namespace nauq {

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
        path(path)
    {
        stbi_set_flip_vertically_on_load(1);

        int w, h, channel;
        stbi_uc* data = stbi_load(path.data(), &w, &h, &channel, 0);
        NQ_CORE_ASSERT(data, "Failed to load image");

        width = w;
        height = h;

        GLenum internalFormat, dataFormat;

        switch (channel) {
            case 4:
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
                break;

            case 3:
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
                break;

            default:
                internalFormat = 0;
                dataFormat = 0;
        }

        NQ_CORE_ASSERT(internalFormat & dataFormat, "Format not supported");

        glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
        glTextureStorage2D(rendererID, 1, internalFormat, width, height);

        glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &rendererID);
    }



    void OpenGLTexture2D::bind(std::uint32_t slot) const
    {
        glBindTextureUnit(slot, rendererID);
    }


}