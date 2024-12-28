#include <iostream>
#include <SDL2/SDL.h>

#include "GLManager.hpp"

int main()
{
    GLManager gl_manager;
    gl_manager.init(); 

    gl_manager.create_graphics_pipeline();

    SDL_Event event;
    while(true)
    {
        {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT)
            {
                break;
            }

            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    break;
                }
            }
        }

        gl_manager.render_quad();
        gl_manager.swap_window();
    }
    
    return 0;
}