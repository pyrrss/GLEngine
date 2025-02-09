#ifndef MESH3D_HPP
#define MESH3D_HPP

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "glad/glad.h"
#include "Shader.hpp"
#include "Texture.hpp"
#include "MeshType.h"

class Mesh3D
{
    private:
        glm::mat4 m_model_matrix = glm::mat4(1.0f); // -> TRS 
        std::vector<GLfloat> m_vertex_data; 
        std::vector<GLuint> m_index_data;
        std::string type;

    public:
        Mesh3D() = default;
        ~Mesh3D();
        void create_mesh(std::vector<GLfloat> vertex_data, std::vector<GLuint> index_data); // -> setea VBO, VAO y EBO
        void translate(float x, float y, float z); // -> traslada el objeto
        void rotate(float angle, glm::vec3 axis); // -> rota el objeto
        void scale(float x, float y, float z); // -> escala el objeto

        int get_num_indices() const;
        int get_num_vertices() const;

        void set_shader(Shader *shader);
        
        void add_texture(Texture *texture);
        void bind_textures();    

        glm::mat4 get_model_matrix();

        GLuint m_vao, m_vbo, m_ebo;

        Shader *m_shader = nullptr;
        std::vector<Texture*> m_textures;

        MeshType m_type = MeshType::DEFAULT;
};

#endif
