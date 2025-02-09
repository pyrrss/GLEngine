#version 410 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_texcoord;
layout(location = 3) in vec3 a_normal;

uniform mat4 u_model;
uniform mat4 u_perspective_projection;
uniform mat4 u_view;

out vec3 v_color; 
out vec3 v_normal;
out vec3 v_frag_position;

void main()
{
    vec4 pos = u_perspective_projection * u_view * u_model * vec4(a_position, 1.0f);

    gl_Position = vec4(pos.x, pos.y, pos.z, pos.w);

    v_color = a_color;
    
    // -> normal del fragmento se transforma a coordenadas del mundo
    // -> aplicando matriz normal (inversa de la transpuesta de la matriz de modelo)
    mat3 normal_matrix = transpose(inverse(mat3(u_model)));
    v_normal = normalize(normal_matrix * a_normal);

    v_frag_position = vec3(u_model * vec4(a_position, 1.0f));

}
