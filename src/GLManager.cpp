#include <SDL2/SDL.h>
#include <algorithm>
#include <fstream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <iostream>
#include <vector>

#include "../include/glad/glad.h"
#include "../include/GLManager.hpp"

void GLManager::show_gl_version_info() const 
{
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
        << "\n";
}

void GLManager::debug_message(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar *message, const void *user_param) 
{
    std::string message_str(message, length);
    std::cout << "GL Debug Message: " << message_str << "\n";
}

void GLManager::enable_debug() const 
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debug_message, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
            GL_TRUE);
}

void GLManager::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow(
            "OpenGL", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED,
            800, 
            600, 
            SDL_WINDOW_OPENGL
    );

    if (window == nullptr)
    {
        std::cerr << "Error al crear ventana: " << SDL_GetError() << std::endl;
        exit(1);
    }

    context = SDL_GL_CreateContext(window);

    if (context == nullptr) 
    {
        std::cerr << "Error al crear contexto OpenGL: " << SDL_GetError()
            << std::endl;
        exit(1);
    }

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) 
    {
        std::cerr << "Error al inicializar GLAD" << std::endl;
        exit(1);
    }

    SDL_WarpMouseInWindow(window, 800/2, 600/2);
    SDL_SetRelativeMouseMode(SDL_TRUE);
 
    show_gl_version_info();
}

const std::string GLManager::load_shaders(const std::string &shader_src) 
{
    std::ifstream file(shader_src);
    std::string source;

    if (file.is_open()) 
    {
        std::string line;
        while (std::getline(file, line)) 
        {
            source += line + "\n";
        }

        file.close();
    }

    return source;
}

GLuint GLManager::compile_shader(const std::string &shader_src, GLenum shader_type)
{
    GLuint shader = glCreateShader(shader_type);
    const char *src = shader_src.c_str();
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

void GLManager::set_shaders()
{

    const std::string vertex_shader_source =
        load_shaders("./shaders/vertex_shader_src.glsl");
    const std::string fragment_shader_source =
        load_shaders("./shaders/frag_shader_src.glsl");

    // -> crear shader program
    shader_program = glCreateProgram();

    // -> compilación de shaders
    GLuint vertex_shader = compile_shader(vertex_shader_source, GL_VERTEX_SHADER);
    GLuint fragment_shader =
        compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER);

    // -> adjuntar shaders al programa
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    // -> enlazar programa
    glLinkProgram(shader_program);

    // -> verificar errores de enlace
    GLint success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar info_log[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        std::cerr << "Error al enlazar shaders: " << info_log << std::endl;
    }

    // -> limpiar shaders (ya están adjuntados al programa de shaders)
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void GLManager::create_graphics_pipeline() 
{
    // Pipeline de OpenGL
    set_shaders();
}

void GLManager::pre_render()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, 800, 600);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
}

void GLManager::render_mesh(Mesh3D *mesh) 
{
    // -> MVP (Model, View, Projection), Model = T * R * S
    glm::mat4 model_matrix = mesh->get_model_matrix();
    projection_matrix = this->camera->get_projection_matrix();
    view_matrix = this->camera->get_view_matrix();

    float current_time = (float) SDL_GetTicks() / 1000.0f;

    // -> uniforms
    GLint time_location = glGetUniformLocation(shader_program, "u_time");
    GLint u_model_location = glGetUniformLocation(shader_program, "u_model");
    GLint u_projection_matrix_location = glGetUniformLocation(shader_program, "u_perspective_projection");
    GLint u_view_matrix_location = glGetUniformLocation(shader_program, "u_view");

    glUniform1f(time_location, current_time);
    glUniformMatrix4fv(u_model_location, 1, GL_FALSE, &model_matrix[0][0]);
    glUniformMatrix4fv(u_projection_matrix_location, 1, GL_FALSE, &projection_matrix[0][0]);
    glUniformMatrix4fv(u_view_matrix_location, 1, GL_FALSE, &view_matrix[0][0]);

    glBindVertexArray(mesh->m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_ebo);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GLManager::swap_window()
{ 
    SDL_GL_SwapWindow(window); 
}

void GLManager::set_camera(Camera *camera)
{
    this->camera = camera;
}

GLManager::~GLManager()
{

    std::cout << "Liberando recursos de GLManager" << std::endl;

    if (shader_program)
    {
        glDeleteProgram(shader_program);
    }

    if (context)
    {
        SDL_GL_DeleteContext(context);
    }

    if (window)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}
