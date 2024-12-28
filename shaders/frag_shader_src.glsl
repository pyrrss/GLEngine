#version 410 core

in vec3 v_color; // -> se recibe el color del vertex shader

out vec4 frag_color; // -> se envía el color final al framebuffer

uniform float u_time;

void main()
{
    float pulse_speed = 1.0f;
    float intensity = (sin(u_time * pulse_speed) + 1.0f) / 2.0f;
    vec3 pulsating_color = v_color * intensity;

    frag_color = vec4(pulsating_color, 1.0);
}

