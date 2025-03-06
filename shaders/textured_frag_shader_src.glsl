#version 410 core

in vec3 v_color;
in vec2 v_texcoord;

out vec4 frag_color; 

uniform sampler2D u_texture0; // -> unidad de textura 0 por defecto cuando se usa una textura
                             // -> por defecto no es necesario asignarle un valor desde CPU
                             // -> a menos que se ocupe otra unidad de textura
uniform sampler2D u_texture1; // -> unidad de textura 1
                             
void main()
{
    frag_color = mix(texture(u_texture0, v_texcoord), texture(u_texture1, v_texcoord), 0.2)
                 * vec4(v_color, 1.0);
}
