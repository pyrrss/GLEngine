#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform float uv_offset;
uniform float uh_offset;
uniform vec2 u_mouse_pos;

out vec3 v_color; 

void main()
{
    vec4 pos = vec4(position.x + uh_offset, position.y + uv_offset, position.z, 1.0f);

    pos.x = clamp(pos.x, -1.0f, 1.0f);
    pos.y = clamp(pos.y, -1.0f, 1.0f);

    gl_Position = pos;

    v_color = color;
}