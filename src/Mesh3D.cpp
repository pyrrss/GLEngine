#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "../include/glad/glad.h"
#include "../include/Mesh3D.hpp"


void Mesh3D::create_mesh(std::vector<GLfloat> vertex_data, std::vector<GLuint> index_data)
{
    m_vertex_data = vertex_data;
    m_index_data = index_data;

    // -> crear VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // -> crear VBO
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
            GL_ARRAY_BUFFER, 
            sizeof(GLfloat) * m_vertex_data.size(), 
            m_vertex_data.data(), 
            GL_STATIC_DRAW
    );

    // -> especificar atributos de vértices
    glEnableVertexAttribArray(0);                  // -> habilita el atributo de vértice 0 (posición)
    glVertexAttribPointer(
            0, // -> atributo de vértice 0
            3, // -> 3 componentes de posición (xyz)
            GL_FLOAT,            // > tipo de dato
            GL_FALSE,            // -> normalizar
            sizeof(GLfloat) * 11, // -> stride
            0                    // -> offset
    );

    glEnableVertexAttribArray(1); // -> habilita el atributo de vértice 1 (color)
    glVertexAttribPointer(
            1,                   // -> atributo de vértice 1
            3,                   // -> 3 componentes de color (rgb)
            GL_FLOAT,            // -> tipo de dato
            GL_FALSE,            // -> normalizar
            sizeof(GLfloat) * 11, // -> stride
            (GLvoid *)(sizeof(GLfloat) * 3) // -> offset (rgb empieza en la posición 3)
    );

    glEnableVertexAttribArray(2); // -> habilita el atributo de vértice 2 (uv)
    glVertexAttribPointer(
            2,                  // -> atributo de vértice 2
            2,                  // -> 2 componentes de uv (uv)
            GL_FLOAT,          // -> tipo de dato
            GL_FALSE,         // -> normalizar
            sizeof(GLfloat) * 11, // -> stride
            (GLvoid *)(sizeof(GLfloat) * 6)  // -> offset (uv empieza en la posición 6)
    );

    glEnableVertexAttribArray(3); // -> habilita el atributo de vértice 3 (normal)
    glVertexAttribPointer(
        3,                 // -> atributo de vértice 3
        3,                 // -> 3 componentes de normal (xyz)
        GL_FLOAT,        // -> tipo de dato
        GL_FALSE,        // -> normalizar
        sizeof(GLfloat) * 11, // -> stride
        (GLvoid *)(sizeof(GLfloat) * 8) // -> offset (normal empieza en la posición 8)
    );

    // -> crear IBO / EBO

    if(!m_index_data.empty())
    {
        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER, 
                sizeof(GLuint) * m_index_data.size(),
                m_index_data.data(), 
                GL_STATIC_DRAW 
        );
    }

    // -> limpiar
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

void Mesh3D::translate(float x, float y, float z)
{
    m_model_matrix = glm::translate(m_model_matrix, glm::vec3(x, y, z));
}

void Mesh3D::rotate(float angle, glm::vec3 axis)
{
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(angle), axis);
}

void Mesh3D::scale(float x, float y, float z)
{
    m_model_matrix = glm::scale(m_model_matrix, glm::vec3(x, y, z));
}

int Mesh3D::get_num_indices() const
{
    return m_index_data.size();
}

int Mesh3D::get_num_vertices() const
{
    return m_vertex_data.size() / 8; // -> 8 componentes por vértice
}

void Mesh3D::set_shader(Shader *shader)
{
    this->m_shader = shader;
}

void Mesh3D::add_texture(Texture *texture)
{
    m_textures.push_back(texture);
}

void Mesh3D::bind_textures()
{
    for (int i = 0; i < m_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        m_textures[i]->bind();
        m_shader->set_uniform_1i("u_texture" + std::to_string(i), i);
    }
}

glm::mat4 Mesh3D::get_model_matrix()
{
    return m_model_matrix;
}

Mesh3D::~Mesh3D()
{
    std::cout << "Liberando recursos de Mesh3D" << std::endl;

    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}
