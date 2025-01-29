#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../include/glad/glad.h"
#include "../include/GLManager.hpp"
#include "../include/Camera.hpp"

void handle_keyboard_input(GLManager *gl_manager, Camera *camera, bool *running)
{
    const Uint8 *k_state = SDL_GetKeyboardState(NULL);

    if (k_state[SDL_SCANCODE_ESCAPE]) 
    {
        *running = false;
    }

    if (k_state[SDL_SCANCODE_UP])
    {
    }

    if (k_state[SDL_SCANCODE_DOWN]) 
    {
    }

    if (k_state[SDL_SCANCODE_LEFT])
    {
    }

    if (k_state[SDL_SCANCODE_RIGHT])
    {
    }

    if(k_state[SDL_SCANCODE_W])
    {
        camera->move_forward(0.1f);
    }

    if(k_state[SDL_SCANCODE_S])
    {
        camera->move_backward(0.1f);
    }

    if(k_state[SDL_SCANCODE_A])
    {
        camera->move_left(0.1f);
    }

    if(k_state[SDL_SCANCODE_D])
    {
        camera->move_right(0.1f);
    }

}

int main() 
{
    GLManager gl_manager;
    gl_manager.init();
    gl_manager.enable_debug();
    
    gl_manager.create_graphics_pipeline();

    Camera camera = Camera();
    camera.set_projection_matrix(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    gl_manager.set_camera(&camera);
 
    // Test de varios Mesh3D
    
    std::vector<GLfloat> mesh1_vertices = {
        // -> 0 - vértice 1
        -0.3f, -0.3f, 0.0f, // -> v inferior izquierdo
            0.0f, 1.0f, 1.0f,   // -> rgb
                                // -> 1 - vértice 2
            0.3f, -0.3f, 0.0f,  // -> v inferior derecho
            1.0f, 0.0f, 1.0f,   // -> rgb
                                // -> 2 - vértice 3
            0.3f, 0.3f, 0.0f,   // -> v superior derecho
            0.0f, 1.0f, 1.0f,   // -> rgb
                                // -> 3 - vértice 4
            -0.3f, 0.3f, 0.0f,  // -> v superior izquierdo
            1.0f, 0.0f, 1.0f,   // -> rgb

    };

    std::vector<GLfloat> mesh2_vertices = {
        // -> 0 - vértice 1
        -0.7f, -0.7f, 0.0f,     // -> v inferior izquierdo
            1.0f, 0.0f, 0.0f,   // -> rgb
                                // -> 1 - vértice 2
            0.7f, -0.7f, 0.0f,  // -> v inferior derecho
            0.0f, 1.0f, 0.0f,   // -> rgb
                                // -> 2 - vértice 3
            0.7f, 0.7f, 0.0f,   // -> v superior derecho
            0.0f, 0.0f, 1.0f,   // -> rgb
                                // -> 3 - vértice 4
            -0.7f, 0.7f, 0.0f,  // -> v superior izquierdo
            1.0f, 1.0f, 0.0f,   // -> rgb

    };

    std::vector<GLfloat> mesh3_vertices = {
        // -> 0 - vértice 1
        -1.0f, -1.0f, 0.0f,     // -> v inferior izquierdo
            0.0f, 1.0f, 1.0f,   // -> rgb
                                // -> 1 - vértice 2
            1.0f, -1.0f, 0.0f,  // -> v inferior derecho
            1.0f, 0.0f, 1.0f,   // -> rgb
                                // -> 2 - vértice 3
            1.0f, 1.0f, 0.0f,   // -> v superior derecho
            0.0f, 1.0f, 1.0f,   // -> rgb
                                // -> 3 - vértice 4
            -1.0f, 1.0f, 0.0f,  // -> v superior izquierdo
            1.0f, 0.0f, 1.0f,   // -> rgb

    };

    // -> ARREGLAR RENDERIZADO DE MULTIPLES MESHES
    std::vector<Mesh3D> meshes;

    /*
    for(int i = 0;i < 10;i++)
    {
        Mesh3D mesh = Mesh3D();
        mesh.create_mesh(mesh1_vertices);
        mesh.m_x_position = 0.0f;
        mesh.m_y_position = 0.0f;
        mesh.u_depth_offset = -2.0f;
        meshes.push_back(mesh);
    }
    */

    Mesh3D mesh1 = Mesh3D();
    mesh1.create_mesh(mesh1_vertices);
    mesh1.translate(0.0f, 0.0f, -2.0f);

    Mesh3D mesh2 = Mesh3D();
    mesh2.create_mesh(mesh2_vertices);
    mesh2.translate(2.0f, 0.0f, -2.0f);

    Mesh3D mesh3 = Mesh3D();
    mesh3.create_mesh(mesh3_vertices);
    mesh3.translate(5.0f, 0.0f, -2.0f);

    SDL_Event event;

    bool running = true;
    while (running) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                running = false;
            }

            if (event.type == SDL_MOUSEMOTION) 
            {
                camera.mouse_look(event.motion.xrel, event.motion.yrel);
            }
        }
        
        handle_keyboard_input(&gl_manager, &camera, &running);
        
        gl_manager.pre_render();

     //   for(Mesh3D &mesh : meshes)
     //   {
     //       gl_manager.render_mesh(&mesh);
     //   }
    
        mesh1.rotate(1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        mesh2.rotate(2.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        mesh3.rotate(3.0f, glm::vec3(1.0f, 1.0f, 1.0f));


     // gl_manager.render_mesh(&meshes[0]); // -> esto no funciona por ahora
        gl_manager.render_mesh(&mesh1);
        gl_manager.render_mesh(&mesh2);
        gl_manager.render_mesh(&mesh3);
        
        gl_manager.swap_window();

    }

    return 0;
}
