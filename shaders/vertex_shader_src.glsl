#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 u_model;
uniform mat4 u_perspective_projection;;
uniform mat4 u_view;

out vec3 v_color; 

void main()
{
    vec4 pos = u_perspective_projection * u_view * u_model * vec4(position, 1.0f);

    gl_Position = vec4(pos.x, pos.y, pos.z, pos.w);

    v_color = color;
}
