#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <string>

#include "../include/glad/glad.h"
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
    private:
        std::string m_vertex_shader_src;
        std::string m_fragment_shader_src;
    
    public:
        Shader(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
        ~Shader();

        const std::string load_shader(const std::string& shader_src);
        GLuint compile_shader(const std::string& shader_src, GLenum shader_type);
        void use() const;
      
        void set_uniform_1f(const std::string& name, float value) const;
        void set_uniform_mat4f(const std::string& name, glm::mat4 matrix) const;
        void set_uniform_1i(const std::string& name, int value) const;
        void set_uniform_3fv(const std::string &name, glm::vec3 vector) const;

        GLuint shader_program;

};


#endif
