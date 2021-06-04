//
// Created by nauq302 on 22/12/2020.
//

#include "nauq/platform/openGL/OpenGLTexture.hpp"

#include "nauq/core/Log.hpp"
#include "nauq/debug/Instrumentor.hpp"

#include "stb_image.hpp"


namespace nauq {

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) :
        path("No no no"),
        width(width),
        height(height),
        internalFormat(GL_RGBA8),
        dataFormat(GL_RGBA)
    {
        NQ_PROFILE_FUNCTION();

        glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
        glTextureStorage2D(rendererID, 1, internalFormat, width, height);

        glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
        path(path)
    {
        NQ_PROFILE_FUNCTION();

        stbi_set_flip_vertically_on_load(1);

        int w, h, channel;
        stbi_uc* data;
        {
            NQ_PROFILE_SCOPE("stbi_load");
            data = stbi_load(path.c_str(), &w, &h, &channel, 0);
        }

        NQ_CORE_ASSERT(data, "Failed to load image " + path);

        width = w;
        height = h;

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

        glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        NQ_PROFILE_FUNCTION();
        glDeleteTextures(1, &rendererID);

    }

    void OpenGLTexture2D::setData(void* data, size_t size)
    {
        NQ_PROFILE_FUNCTION();

        std::uint32_t bpp = dataFormat == GL_RGBA ? 4 : 3;
        NQ_ASSERT(size == width * height * bpp, "Data must be entire texture");
        glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::bind(uint32_t slot) const
    {
        NQ_PROFILE_FUNCTION();

       glBindTextureUnit(slot, rendererID);
    }

    void OpenGLTexture2D::unbind() const
    {
        NQ_PROFILE_FUNCTION();

        glBindTexture(GL_TEXTURE_2D, 0);
    }




}