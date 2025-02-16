#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

void Texture2D::Load(const std::string& path)
{
    // Cleanup previous texture if exists
    if (m_handle != 0)
    {
        glDeleteTextures(1, &m_handle);
        m_handle = 0;
    }

    // Use glGenTextures instead of glCreateTextures
    glGenTextures(1, &m_handle);
    glBindTexture(GL_TEXTURE_2D, m_handle);

    unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 3);
    if (!data)
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return;
    }

    // Set up immutable storage only if the extension or version supports it;
    // otherwise use glTexImage2D directly
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(data);

    // Unbind for safety
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    if (m_handle == 0)
    {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture2D::Unbind() const
{
    if (m_handle == 0)
    {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}
