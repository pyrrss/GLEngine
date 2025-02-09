#version 410 core

in vec3 v_color;
in vec3 v_normal;
in vec3 v_frag_position;

out vec4 frag_color;

uniform vec3 u_object_color; // -> color del objeto
uniform vec3 u_light_color; // -> color de la luz proyectada sobre el objeto
uniform vec3 u_light_position; // -> posicion de la fuente de luz
uniform vec3 u_view_position; // -> posicion de la camara

void main()
{

    // -> LUZ AMBIENTE
    float ambient_strength = 0.3f; // -> intensidad de la luz ambiente
    vec3 ambient = ambient_strength * u_light_color;

    // -> LUZ DIFUSA
    // -> normalizar la normal (aqui ya esta en coordenadas del mundo)
    vec3 norm = normalize(v_normal);
    // -> direccion de la luz
    vec3 light_direction = normalize(u_light_position - v_frag_position);

    // -> intensidad de la luz (angulo entre normal y direccion de la luz)
    float diff = max(dot(norm, light_direction), 0.0);
    
    vec3 diffuse = diff * u_light_color;
    
    // -> LUZ ESPECULAR
    float specular_strength = 1.2f; // -> intensidad de la luz especular
    vec3 view_direction = normalize(u_view_position - v_frag_position);
    vec3 reflect_direction = reflect(-light_direction, norm);
    
    // -> spec := angulo entre direccion de la vista y direccion de la reflexion
    // -> pow(spec, 32) := brillo del objeto
    // -> 32 := brillo del objeto arbitrario
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 64);
    vec3 specular = specular_strength * spec * u_light_color;

    // -> MODELO PHONG: luz = ambiente + difusa + especular
    // -> color reflejado = (ambiente + difusa + especular) * color_objeto
    vec3 result_color = (ambient + diffuse + specular) * u_object_color;

    // -> color resultante es el "color que refleja el objeto" 
    // -> luego de aplicar la luz sobre el objeto
    frag_color = vec4(result_color, 1.0);
}
