#include <iostream>

#include "../include/Texture.hpp"
#include "../include/glad/glad.h"
#include "../include/stb_image.h"

Texture::Texture(const std::string &image_path)
{
    stbi_set_flip_vertically_on_load(true);

    m_image_data = stbi_load(image_path.c_str(), &m_width, &m_height, &m_nr_channels, 0);
    
    if (m_image_data == nullptr)
    {
        std::cerr << "Error al cargar textura" << std::endl;
        exit(1);
    }

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
   
    // -> configurar textura (esto tengo que leerlo mas en detalle en learnopengl)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // -> S = x
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // -> T = y, R = z (3D)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
    // -> cargar textura
    GLenum format;

    if (m_nr_channels == 1)
    {
        format = GL_RED;
    }
    else if (m_nr_channels == 3)
    {
        format = GL_RGB;
    }
    else if (m_nr_channels == 4)
    {
        format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format,
                  GL_UNSIGNED_BYTE, m_image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // -> liberar memoria de la textura
    stbi_image_free(m_image_data);

}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    std::cout << "Liberando recursos de textura" << std::endl;
    
    glDeleteTextures(1, &m_texture_id);
}
