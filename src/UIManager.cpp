#include <iostream>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl2.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../include/UIManager.hpp"

void UIManager::init(SDL_Window *window, SDL_GLContext context)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void UIManager::process_event(SDL_Event &event)
{
    ImGui_ImplSDL2_ProcessEvent(&event);
    
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_t)
    {
        toggle_visibility();
    }

}

void UIManager::prepare_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void UIManager::render()
{
    if(show_ui)
    {
        ImGui::ShowDemoWindow();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::toggle_visibility()
{
    show_ui = !show_ui;
}

UIManager::~UIManager()
{
    std::cout << "Liberando recursos de UIManager" << std::endl;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
