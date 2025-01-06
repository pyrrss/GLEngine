#version 410 core

in vec3 v_color; 

out vec4 frag_color; 

uniform float uv_offset;
uniform float uh_offset;
uniform float u_time;
uniform vec2 u_mouse_pos;

void main()
{
    float pulse_speed = 3.5f;
    float intensity = (sin(u_time * pulse_speed) + 1.0f) / 2.0f;
    vec3 pulsating_color = v_color * intensity;

    vec2 frag_pos = vec2(gl_FragCoord.x, gl_FragCoord.y);
    frag_pos = (frag_pos / vec2(800.0f, 600.0f)) * 2.0f - 1.0f;
    float distance = length(u_mouse_pos - frag_pos);
    float proximity_effect = smoothstep(0.2f, 0.8f, 1.0f - distance);


    frag_color = vec4(
        (pulsating_color.r * proximity_effect), 
        (pulsating_color.g * proximity_effect), 
        (pulsating_color.b * proximity_effect), 
        1.0
    );
}

