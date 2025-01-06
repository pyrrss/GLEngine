#include <iostream>
#include <SDL2/SDL.h>

#include "GLManager.hpp"

int main() 
{
  GLManager gl_manager;
  gl_manager.init();
  gl_manager.enable_debug();
  gl_manager.create_graphics_pipeline();

  SDL_Event event;
  while (true) 
  {
    
    while(SDL_PollEvent(&event))
    {

      if (event.type == SDL_QUIT) 
      {
        break;
      }

      if(event.type == SDL_MOUSEMOTION)
      {
        gl_manager.set_u_mousepos(event.motion.x, event.motion.y);
      }
    
    }
    
    {
      const Uint8 *k_state = SDL_GetKeyboardState(NULL);

      if (k_state[SDL_SCANCODE_ESCAPE]) 
      {
        break;
      }

      if(k_state[SDL_SCANCODE_UP] || k_state[SDL_SCANCODE_W])
      {
        gl_manager.set_uvoffset(0.01f);
      }

      if(k_state[SDL_SCANCODE_DOWN] || k_state[SDL_SCANCODE_S])
      {
        gl_manager.set_uvoffset(-0.01f);
      }

      if(k_state[SDL_SCANCODE_LEFT] || k_state[SDL_SCANCODE_A])
      {
        gl_manager.set_uhoffset(-0.01f);
      }

      if(k_state[SDL_SCANCODE_RIGHT] || k_state[SDL_SCANCODE_D])
      {
        gl_manager.set_uhoffset(0.01f);
      }

    }

    gl_manager.render_quad();
    gl_manager.swap_window();

  }

  return 0;
}
