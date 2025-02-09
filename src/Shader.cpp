#include <iostream>
#include <string>
#include <fstream>

#include "../include/glad/glad.h"
#include "../include/Shader.hpp"


Shader::Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    m_vertex_shader_src = load_shader(vertex_shader_path);
    m_fragment_shader_src = load_shader(fragment_shader_path);

    // -> crear shader program
    shader_program = glCreateProgram();

    // -> compilación de shaders
    GLuint vertex_shader = compile_shader(m_vertex_shader_src, GL_VERTEX_SHADER);
    GLuint fragment_shader = compile_shader(m_fragment_shader_src, GL_FRAGMENT_SHADER);

    // -> adjuntar shaders al programa
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    // -> linkear programa
    glLinkProgram(shader_program);

    // -> verificar errores de linkeo
    GLint success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar info_log[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        std::cerr << "Error al linkear programa de shaders: " << info_log << std::endl;
    }

    // -> shaders ya están adjuntados al programa de shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

}

const std::string Shader::load_shader(const std::string& shader_src)
{
    std::ifstream file(shader_src);
    std::string source;
    std::string line;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            source += line + "\n";
        }
    }
    else
    {
        std::cerr << "Error al cargar shader: " << shader_src << std::endl;
    }

    return source;

}

GLuint Shader::compile_shader(const std::string& shader_src, GLenum shader_type)
{
    GLuint shader = glCreateShader(shader_type);
    const char* src = shader_src.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar info_log[512];
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        std::cerr << "Error al compilar shader: " << info_log << std::endl;
    }

    return shader;
}

void Shader::use() const
{
    glUseProgram(shader_program);
}

void Shader::set_uniform_1f(const std::string& name, float value) const
{
    GLint location = glGetUniformLocation(shader_program, name.c_str());

    if(location == -1)
    {
        std::cerr << "Error: Uniform " << name <<" no encontrado" << std::endl;
        return;
    }

    glUniform1f(location, value);
}

void Shader::set_uniform_mat4f(const std::string& name, glm::mat4 matrix) const
{
    GLint location = glGetUniformLocation(shader_program, name.c_str());

    if(location == -1)
    {
        std::cerr << "Error: Uniform " << name <<" no encontrado" << std::endl;
        return;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set_uniform_1i(const std::string& name, int value) const
{
    GLint location = glGetUniformLocation(shader_program, name.c_str());

    if(location == -1)
    {
        std::cerr << "Error: Uniform " << name <<" no encontrado" << std::endl;
        return;
    }

    glUniform1i(location, value);
}

void Shader::set_uniform_3fv(const std::string &name, glm::vec3 vector) const
{
    GLint location = glGetUniformLocation(shader_program, name.c_str());

    if(location == -1)
    {
        std::cerr << "Error: Uniform " << name <<" no encontrado" << std::endl;
        return;
    }

    glUniform3fv(location, 1, &vector[0]);
}


Shader::~Shader()
{
    std::cout << "Liberando recursos de Shader" << std::endl;
    glDeleteProgram(shader_program);
}














