#include <iostream>

#include <SDL2/SDL.h>

class UIManager
{
    private:
        bool show_ui = true;
    
    public: 
        UIManager() = default;
        ~UIManager();
        void init(SDL_Window *window, SDL_GLContext context);
        void process_event(SDL_Event &event);
        void prepare_frame();
        void render();
        void toggle_visibility();

};
