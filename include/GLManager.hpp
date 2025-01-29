#ifndef GLMANAGER_HPP
#define GLMANAGER_HPP

#include <SDL2/SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "../include/glad/glad.h"
#include "../include/Camera.hpp"
#include "Mesh3D.hpp"

class GLManager 
{
    private:
        SDL_Window *window;
        SDL_GLContext context;
        GLuint shader_program; // -> programa de shaders comun a todos los objetos 3D
        float u_depth_offset = -2.0f;
        float u_rotation_angle = 0.0f;
        glm::mat4 projection_matrix; // -> perspectiva 
        glm::mat4 view_matrix; // -> vista (camara)
        Camera *camera;

        void show_gl_version_info() const; // -> muestra info de OpenGL
        static void debug_message(GLenum source, GLenum type, GLuint id, GLenum severity,
                                  GLsizei length, const GLchar *message,
                                  const void *user_param); // -> callback de mensajes de debug
        void set_shaders();      // -> setea shaders
        const std::string load_shaders(const std::string &shader_src); // -> carga shaders desde archivos
        GLuint compile_shader(const std::string &shader_src, GLenum shader_type); // -> compila shaders

    public:
        GLManager() = default;
        ~GLManager();                    // -> libera recursos de SDL y GLAD
        void init();                     // -> inicializa SDL y GLAD
        void enable_debug() const;             // -> habilita mensajes de debug de OpenGL
        void swap_window();              // -> intercambia buffers de ventana
        void create_graphics_pipeline(); // -> crea pipeline de OpenGL
        void pre_render();               // -> configs previas a renderizar
        void render_mesh(Mesh3D *mesh);  // -> renderiza un objeto 3D

        void set_camera(Camera *camera);

};

#endif
