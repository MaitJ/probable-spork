out vec4 FragColor;
in vec2 tex_coords;
in vec3 Normals;
in vec3 frag_pos_world;
uniform sampler2D tex;
uniform bool is_textured;
uniform vec3 light_pos;
uniform vec3 camera_pos;

void main() {
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    vec3 normalized_normals = normalize(Normals);
    vec3 light_dir = normalize(light_pos - frag_pos_world);

    float ambient_strength = 0.1f;
    float specular_strength = 0.5f;

    vec3 diffuse = calculateDiffuseColor(normalized_normals, light_dir, light_color);

    vec3 specular = calculateSpecularColor(camera_pos, frag_pos_world, light_dir, normalized_normals,
    specular_strength, light_color);

    if (is_textured) {
        vec3 tex_color = texture(tex, tex_coords).rgb;
        vec3 ambient = calculateAmbientColor(tex_color, ambient_strength);
        vec3 ambi_diff_color = (ambient + diffuse + specular) * tex_color;
        FragColor = vec4(ambi_diff_color, 1.0f);
    } else {
        vec3 def_color = vec3(0.9f, 0.9f, 0.9f);
        vec3 ambient = calculateAmbientColor(def_color, ambient_strength);
        vec3 ambi_diff_color = (ambient + diffuse + specular) * def_color;
        FragColor = vec4(ambi_diff_color, 1.0f);
    }
}
