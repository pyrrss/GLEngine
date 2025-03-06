#include <SDL2/SDL.h>
#include <algorithm>
#include <fstream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <iostream>
#include <vector>

#include "../include/glad/glad.h"
#include "../include/GLManager.hpp"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl2.h"
#include "../imgui/imgui_impl_opengl3.h"

void GLManager::show_gl_version_info() const 
{
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
              << "\n";

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Máximo de atributos de vértices: " << nrAttributes << "\n";
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

void GLManager::toggle_mouse_capture()
{
    mouse_captured= !mouse_captured;

    if(mouse_captured)
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_WarpMouseInWindow(window, 800 / 2, 600 / 2);
    }
    else
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }

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

void GLManager::pre_render()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, 800, 600);
    glClearColor(0.106, 0.168, 0.203, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLManager::render_mesh(Mesh3D *mesh) 
{
    if(mesh == nullptr)
    {
        std::cerr << "Error: Mesh inválido" << std::endl;
        return;
    }

    if(mesh->m_shader == nullptr)
    {
        std::cerr << "Error: Shader de mesh inválido" << std::endl;
        return;
    }

    // -> evita cambiar de shader si no es necesario
    static Shader *last_shader = nullptr;
    if(last_shader != mesh->m_shader)
    {
        mesh->m_shader->use();
        last_shader = mesh->m_shader;
    }
    
    switch(mesh->m_type)
    {
        case MeshType::DEFAULT:
        {
            float current_time = (float) SDL_GetTicks() / 1000.0f;
            mesh->m_shader->set_uniform_1f("u_time", current_time);
            break;
        }

        case MeshType::TEXTURED:
        {
            mesh->bind_textures();
            break;
        }   
        
        case MeshType::LIGHT_SOURCE:
        {
            break;
        }
        
        case MeshType::LIGHT_RECEIVER:
        {
            mesh->bind_textures();

            mesh->m_shader->set_uniform_3fv("u_light_position", light_position);
            mesh->m_shader->set_uniform_3fv("u_view_position", camera->get_position());
            break;
        }

        case MeshType::CUSTOM:
        {
            break;
        }

        default:
        {
            break;
        }
    }

    // -> setear matrices de transformacion MVP para vertex shader
    mesh->m_shader->set_uniform_mat4f("u_model", mesh->get_model_matrix());
    mesh->m_shader->set_uniform_mat4f("u_perspective_projection", this->camera->get_projection_matrix());
    mesh->m_shader->set_uniform_mat4f("u_view", this->camera->get_view_matrix());

    glBindVertexArray(mesh->m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo);

    // -> renderizacion indexada / no indexada
    if(mesh->m_ebo != 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_ebo);
        glDrawElements(GL_TRIANGLES, mesh->get_num_indices(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, mesh->get_num_vertices());
    }

    // -> deseleccionar texturas activas en caso de que haya
    if(!mesh->m_textures.empty())
    {
        for (int i = 0; i < mesh->m_textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

}

void GLManager::swap_window()
{ 
    SDL_GL_SwapWindow(window); 
}

void GLManager::set_camera(Camera *camera)
{
    this->camera = camera;
}

SDL_Window* GLManager::get_window() const
{
    return window;
}

SDL_GLContext GLManager::get_context() const
{
    return context;
}

GLManager::~GLManager()
{

    std::cout << "Liberando recursos de GLManager" << std::endl;


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
