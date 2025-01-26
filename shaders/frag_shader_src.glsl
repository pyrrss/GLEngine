#version 410 core

in vec3 v_color; 

out vec4 frag_color; 

uniform float u_time;

void main()
{
    float pulse_speed = 3.5f;
    float intensity = (sin(u_time * pulse_speed) + 1.0f) / 2.0f;
    vec3 pulsating_color = v_color * intensity;

    vec2 frag_pos = vec2(gl_FragCoord.x, gl_FragCoord.y);
    frag_pos = (frag_pos / vec2(800.0f, 600.0f)) * 2.0f - 1.0f;

    frag_color = vec4(
        (pulsating_color.r), 
        (pulsating_color.g), 
        (pulsating_color.b), 
        1.0
    );
}

