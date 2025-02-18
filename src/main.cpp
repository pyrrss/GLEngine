#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../include/Camera.hpp"
#include "../include/GLManager.hpp"
#include "../include/Shader.hpp"
#include "../include/glad/glad.h"
#include "../include/stb_image.h"
#include "../include/Texture.hpp"
#include "../include/VertexData.hpp"
#include "../include/MeshType.h"
#include "../include/UIManager.hpp"


void handle_keyboard_input(GLManager *gl_manager, Camera *camera, Mesh3D *light_source_cube)
{
    const Uint8 *k_state = SDL_GetKeyboardState(NULL);

    if (k_state[SDL_SCANCODE_UP]) 
    {
        gl_manager->light_position.y -= 0.1f;
        light_source_cube->translate(0.0f, 0.1f, 0.0f);
    }

    if (k_state[SDL_SCANCODE_DOWN]) 
    {
        gl_manager->light_position.y += 0.1f;
        light_source_cube->translate(0.0f, -0.1f, 0.0f);
    }

    if (k_state[SDL_SCANCODE_LEFT]) 
    {
        gl_manager->light_position.x -= 0.1f;
        light_source_cube->translate(-0.1f, 0.0f, 0.0f);
    }

    if (k_state[SDL_SCANCODE_RIGHT]) 
    {
        gl_manager->light_position.x += 0.1f;
        light_source_cube->translate(0.1f, 0.0f, 0.0f);
    }

    if (k_state[SDL_SCANCODE_W])
    {
        camera->move_forward(0.1f);
    }

    if (k_state[SDL_SCANCODE_S]) 
    {
        camera->move_backward(0.1f);
    }

    if (k_state[SDL_SCANCODE_A]) 
    {
        camera->move_left(0.1f);
    }

    if (k_state[SDL_SCANCODE_D])
    {
        camera->move_right(0.1f);
    }

}

int main() 
{
    
    // -> Manejador de OpenGL
    GLManager gl_manager;
    gl_manager.init();
    gl_manager.enable_debug();

    // -> GUI
    UIManager ui_manager;
    ui_manager.init(gl_manager.get_window(), gl_manager.get_context());

    // -> Cámara
    Camera camera = Camera();
    camera.set_projection_matrix(90.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    gl_manager.set_camera(&camera);

    // -> Shaders
    Shader untextured_shader = Shader("shaders/my_vertex_shader_src.glsl",
                                      "shaders/my_frag_shader_src.glsl");
    Shader textured_shader = Shader("shaders/textured_vertex_shader_src.glsl", 
                                    "shaders/textured_frag_shader_src.glsl");
    Shader light_source_shader = Shader("shaders/my_vertex_shader_src.glsl", 
                                    "shaders/light_source_frag_shader_src.glsl");
    Shader light_receiver_shader = Shader("shaders/my_vertex_shader_src.glsl", 
                                    "shaders/light_receiver_frag_shader_src.glsl");

    // Test de meshes de ejemplo

    std::vector<Mesh3D*> meshes;      

    Mesh3D mesh1 = Mesh3D();
    mesh1.create_mesh(VertexData::mesh1_vertex_data, {0, 1, 2, 0, 2, 3});
    mesh1.translate(0.0f, 2.0f, -2.0f);
    mesh1.set_shader(&untextured_shader);
    mesh1.m_type = MeshType::DEFAULT;
    meshes.push_back(&mesh1);


    Mesh3D mesh2 = Mesh3D();
    mesh2.create_mesh(VertexData::mesh2_vertex_data, {0, 1, 2, 0, 2, 3});
    mesh2.translate(2.0f, 2.0f, -2.0f);
    mesh2.set_shader(&untextured_shader);
    mesh1.m_type = MeshType::DEFAULT;
    meshes.push_back(&mesh2);

    Mesh3D mesh3 = Mesh3D();
    mesh3.create_mesh(VertexData::mesh3_vertex_data, {0, 1, 2, 0, 2, 3});
    mesh3.translate(6.0f, 2.0f, -2.0f);
    mesh3.set_shader(&untextured_shader);
    mesh1.m_type = MeshType::DEFAULT;
    meshes.push_back(&mesh3);

    //std::unique_ptr<Mesh3D> model =
    //    ObjectLoader::load_object("models/jeep_v02.obj");


    // -> Texturas
    
    Texture container_texture = Texture("assets/container.jpg");
    Texture awesome_texture = Texture("assets/awesomeface.png");

    // -> ejemplo quad con textura
    Mesh3D textured_mesh = Mesh3D();
    textured_mesh.create_mesh(VertexData::vertices, {0, 1, 2, 0, 2, 3});
    textured_mesh.translate(11.0f, 2.0f, -2.0f);
    textured_mesh.set_shader(&textured_shader);
    textured_mesh.add_texture(&container_texture);
    textured_mesh.add_texture(&awesome_texture);
    textured_mesh.m_type = MeshType::TEXTURED;
    meshes.push_back(&textured_mesh);

    // -> ejemplo cubo con textura
    Mesh3D textured_cube = Mesh3D();
    textured_cube.create_mesh(VertexData::cube_vertex_data, {});
    textured_cube.translate(20.0f, 2.0f, -2.0f);
    textured_cube.scale(5.0f, 5.0f, 5.0f);
    textured_cube.set_shader(&textured_shader);
    textured_cube.add_texture(&container_texture);
    textured_cube.add_texture(&awesome_texture);
    textured_cube.m_type = MeshType::TEXTURED;
    meshes.push_back(&textured_cube);

    // -> ejemplo piramide 3D
    Mesh3D textured_pyramid = Mesh3D();
    textured_pyramid.create_mesh(VertexData::pyramid_vertex_data, {});
    textured_pyramid.translate(32.0f, -1.0f, -2.0f);
    textured_pyramid.scale(7.0f, 13.0f, 7.0f);
    textured_pyramid.set_shader(&textured_shader);
    textured_pyramid.add_texture(&container_texture);
    textured_pyramid.add_texture(&awesome_texture);
    textured_pyramid.m_type = MeshType::TEXTURED;
    meshes.push_back(&textured_pyramid);

    // -> TODO: Hacer un suelo para la escena global


    // -> LIGHTING
    
    glm::vec3 light_position = gl_manager.light_position; // -> posición de la luz
                                                            // -> en el espacio del mundo
    Mesh3D light_source_cube = Mesh3D();
    light_source_cube.create_mesh(VertexData::light_source_vertex_data, {});
    light_source_cube.translate(light_position.x, light_position.y, light_position.z);
    light_source_cube.set_shader(&light_source_shader);
    light_source_cube.m_type = MeshType::LIGHT_SOURCE;
    meshes.push_back(&light_source_cube);

    Mesh3D light_receiver_cube = Mesh3D();
    light_receiver_cube.create_mesh(VertexData::light_receiver_vertex_data, {});
    light_receiver_cube.translate(5.0f, 2.0f, 4.0f);
    light_receiver_cube.set_shader(&light_receiver_shader);
    light_receiver_cube.m_type = MeshType::LIGHT_RECEIVER;
    meshes.push_back(&light_receiver_cube);
    
    light_receiver_shader.use();
    light_receiver_shader.set_uniform_3fv("u_object_color", glm::vec3(1.0f, 0.5f, 0.31f));
    light_receiver_shader.set_uniform_3fv("u_light_color", glm::vec3(1.0f, 1.0f, 1.0f));
    light_receiver_shader.set_uniform_3fv("u_light_position", light_position);

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

            if (event.type == SDL_MOUSEMOTION && gl_manager.mouse_captured) 
            {
               camera.mouse_look(event.motion.xrel, event.motion.yrel);
            }

            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_q)
                {
                    gl_manager.toggle_mouse_capture();
                }

                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }

            }

            // ----- ImGui -----
            ui_manager.process_event(event);
                
        }
    
        ui_manager.prepare_frame();

        handle_keyboard_input(&gl_manager, &camera, &light_source_cube);

        mesh1.rotate(1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        mesh2.rotate(2.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        mesh3.rotate(3.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        textured_mesh.rotate(4.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        textured_cube.rotate(1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        textured_pyramid.rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        light_receiver_cube.rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        // -> opciones de pre-renderizado
        gl_manager.pre_render();

        // -> renderizado de meshes
        for(Mesh3D *mesh : meshes)
        {
            gl_manager.render_mesh(mesh);
        }

        // -> renderizado de GUI
        ui_manager.render();

        // -> doble-buffer
        gl_manager.swap_window();
    }

    return 0;
}
