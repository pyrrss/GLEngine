#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>

#include "../include/glad/glad.h"

class Texture
{
    private:
        unsigned char *m_image_data;
        int m_width;
        int m_height;
        int m_nr_channels;

    public:
        Texture(const std::string &image_path);
        ~Texture();
        void bind();
        void unbind();

        GLuint m_texture_id;


};

#endif
