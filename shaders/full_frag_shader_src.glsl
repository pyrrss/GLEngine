#version 410 core

in vec3 v_color;
in vec2 v_texcoord;
in vec3 v_normal;

in vec3 v_frag_position;

out vec4 frag_color;

uniform sampler2D u_texture0;

uniform vec3 u_object_color; // -> color del objeto (si hay textura no se usa)
uniform vec3 u_light_position; // -> posicion de la fuente de luz
uniform vec3 u_view_position; // -> posicion de la camara

struct Material // -> coeficientes arbitrarios del material
{
    sampler2D diffuse; // -> textura (diffuse map)
    vec3 specular;
    float shininess;
};

uniform Material material;

struct Light 
{
    vec3 position;
    
    // -> color de la luz se descompone en sus componentes
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main()
{
    // * color 
    // * texturizar
    // * iluminacion
    
    // -> texturizado
    vec3 frag_texture = texture(u_texture0, v_texcoord).rgb; 
    
    // -> iluminacion siguiendo modelo PHONG
    
    // -> LUZ AMBIENTE
    // -> intensidad de la luz ambiente (arbitraria)
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_texcoord));

    // -> LUZ DIFUSA
    // -> normalizar la normal (aqui ya esta en coordenadas del mundo)
    vec3 norm = normalize(v_normal);
    // -> direccion de la luz
    vec3 light_direction = normalize(u_light_position - v_frag_position);

    // -> intensidad de la luz (angulo entre normal y direccion de la luz)
    float diff = max(dot(norm, light_direction), 0.0);
    
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_texcoord));
    
    // -> LUZ ESPECULAR
    vec3 view_direction = normalize(u_view_position - v_frag_position);
    vec3 reflect_direction = reflect(-light_direction, norm);
    
    // -> spec := angulo entre direccion de la vista y direccion de la reflexion
    // -> pow(spec, 32) := brillo del objeto
    // -> 32 := brillo del objeto arbitrario (material.shininess)
    // -> material.specular arbitrario
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
    vec3 specular = (spec * material.specular) * light.specular;

    // -> MODELO PHONG: luz = ambiente + difusa + especular
    // -> color reflejado = (ambiente + difusa + especular) * color_objeto
    vec3 result_color = (ambient + diffuse + specular) * frag_texture;

    // -> color resultante es el "color que refleja el objeto" 
    // -> luego de aplicar la luz sobre el objeto
    frag_color = vec4(result_color, 1.0);

}
