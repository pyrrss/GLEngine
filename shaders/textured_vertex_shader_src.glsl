#version 410 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_texcoord;

out vec3 v_color;
out vec2 v_texcoord;

uniform mat4 u_model;
uniform mat4 u_perspective_projection;
uniform mat4 u_view;

void main()
{
    gl_Position = u_perspective_projection * u_view * u_model * vec4(a_position, 1.0f);
    v_color = a_color;
    v_texcoord = a_texcoord;
}
