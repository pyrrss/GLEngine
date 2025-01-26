#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../include/GLManager.hpp"
#include "../include/Camera.hpp"

void handle_keyboard_input(GLManager *gl_manager, Camera *camera)
{
    const Uint8 *k_state = SDL_GetKeyboardState(NULL);

    if (k_state[SDL_SCANCODE_ESCAPE]) 
    {
        exit(0); 
    }

    if (k_state[SDL_SCANCODE_UP])
    {
        gl_manager->set_u_depth_offset(0.05f);
    }

    if (k_state[SDL_SCANCODE_DOWN]) 
    {
        gl_manager->set_u_depth_offset(-0.05f);
    }

    if (k_state[SDL_SCANCODE_LEFT])
    {
        gl_manager->set_u_rotation_angle(-1.0f);
    }

    if (k_state[SDL_SCANCODE_RIGHT])
    {
        gl_manager->set_u_rotation_angle(1.0f);
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
    gl_manager.set_camera(&camera);
 
    SDL_Event event;
    while (true) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            { 
                break;
            }

            if (event.type == SDL_MOUSEMOTION) 
            {
                camera.mouse_look(event.motion.xrel, event.motion.yrel);
            }
        }
        
        handle_keyboard_input(&gl_manager, &camera);

        gl_manager.render_quad();
        gl_manager.swap_window();

    }

    return 0;
}
