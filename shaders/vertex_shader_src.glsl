#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 v_color; // -> se envía el color al fragment shader

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    v_color = color;
}