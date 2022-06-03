out vec4 FragColor;
in vec2 tex_coords;
in vec3 Normals;
in vec3 frag_pos_world;
uniform vec3 light_pos;
uniform vec3 camera_pos;
uniform vec3 vertex_color;

void main() {
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    vec3 normalized_normals = normalize(Normals);
    vec3 light_dir = normalize(light_pos - frag_pos_world);

    float ambient_strength = 0.1f;
    float specular_strength = 0.5f;

    vec3 diffuse = calculateDiffuseColor(normalized_normals, light_dir, light_color);

    vec3 specular = calculateSpecularColor(camera_pos, frag_pos_world, light_dir, normalized_normals,
    specular_strength, light_color);

    vec3 ambient = calculateAmbientColor(vertex_color, ambient_strength);
    vec3 ambi_diff_color = (ambient + diffuse + specular) * vertex_color;
    FragColor = vec4(ambi_diff_color, 1.0f);
}
