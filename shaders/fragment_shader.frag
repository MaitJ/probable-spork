#version 330 core

out vec4 FragColor;

in vec2 tex_coords;
in vec3 Normals;
in vec3 frag_pos_world;

uniform sampler2D tex;
uniform bool is_textured;
uniform vec3 light_pos;

void main() {
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    vec3 normal = normalize(Normals);
    vec3 light_dir = normalize(light_pos - frag_pos_world);

    float ambient_strength = 0.1f;

    float diff = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    if (is_textured) {
        vec3 tex_color = texture(tex, tex_coords).rgb;
        vec3 ambient = tex_color * ambient_strength;
        vec3 ambi_diff_color = (ambient + diffuse) * tex_color;
        FragColor = vec4(ambi_diff_color, 1.0f);
    } else {
        vec3 def_color = vec3(0.9f, 0.9f, 0.9f);
        vec3 ambient = def_color * ambient_strength;
        vec3 ambi_diff_color = (ambient + diffuse) * def_color;
        FragColor = vec4(ambi_diff_color, 1.0f);
    }
}
