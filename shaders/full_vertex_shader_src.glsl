#version 410 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_texcoord;
layout(location = 3) in vec3 a_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_perspective_projection;

out vec3 v_color; 
out vec2 v_texcoord;
out vec3 v_normal;

out vec3 v_frag_position;

void main()
{
    gl_Position = u_perspective_projection * u_view * u_model * vec4(a_position, 1.0f);

    // -> normal del fragmento se transforma a coordenadas del mundo
    // -> aplicando matriz normal (inversa de la transpuesta de la matriz de modelo)
    mat3 normal_matrix = transpose(inverse(mat3(u_model)));
    v_normal = normalize(normal_matrix * a_normal);

    v_color = a_color;
    v_texcoord = a_texcoord;
    v_frag_position = vec3(u_model * vec4(a_position, 1.0f));
}

