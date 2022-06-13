#include "texture.h"
#include <stb/stb_image.h>
#include <stdio.h>
Texture::Texture(GLenum textureTarget, const std::string& fileName)
{
    m_textureTarget = textureTarget;
    m_fileName = fileName;
}

bool Texture::Load()
{
    return Load(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

bool Texture::Load(GLint wrapS, GLint wrapT)
{
    // texture space goes from bottom to top in open gl, so we need to flip the image
    stbi_set_flip_vertically_on_load(1);
    int width, height, bpp;

    unsigned char* imageData = stbi_load(m_fileName.c_str(), &width, &height, &bpp, 0);

    if (imageData == nullptr)
    {
        printf("Failed to load texture: ");
        exit(1);
    }

    glGenTextures(1, &m_textureId);
    glBindTexture(m_textureTarget, m_textureId);
    if (m_textureTarget == GL_TEXTURE_2D)
    {
        glTexImage2D(m_textureTarget, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    }
    else if (m_textureTarget == GL_TEXTURE_CUBE_MAP)
    {
        for (int i = 0; i < 6; i++)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        }
    }
    glTexParameteri(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_T, wrapT);
    glBindTexture(m_textureTarget, 0);

    stbi_image_free(imageData);

    return true;
}

void Texture::Bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(m_textureTarget, m_textureId);
}