#ifndef GLMANAGER_HPP
#define GLMANAGER_HPP

#include <SDL2/SDL.h>

#include "../include/glad/glad.h"

class GLManager
{
    private:
        SDL_Window* window;
        SDL_GLContext context;
        GLuint vao;
        GLuint vbo;
        GLuint ibo;
        GLuint shader_program;
        
        void show_gl_version_info(); // -> muestra info de OpenGL
        static void debug_message(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param); // -> callback de mensajes de debug
        void specify_vertices(); // -> especifica vertices y setea VAO y VBO
        void set_shaders(); // -> setea shaders
        const std::string load_shaders(const std::string& shader_src); // -> carga shaders desde archivos
        GLuint compile_shader(const std::string& shader_src, GLenum shader_type); // -> compila shaders

    public:
        GLManager() = default;
        ~GLManager(); // -> libera recursos de SDL y GLAD
        void init(); // -> inicializa SDL y GLAD
        void enable_debug(); // -> habilita mensajes de debug de OpenGL
        void swap_window(); // -> intercambia buffers de ventana
        void create_graphics_pipeline(); // -> crea pipeline de OpenGL
        void render_quad(); // -> renderiza cuadrado
};

#endif