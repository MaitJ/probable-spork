#version 330 core

vec3 calculateAmbientColor(in vec3 color, in float ambient_strength) {
    return(color * ambient_strength);
}

vec3 calculateDiffuseColor(in vec3 normals, in vec3 light_dir, in vec3 light_color) {
    float diff = max(dot(normals, light_dir), 0.0f);
    return(diff * light_color);
}

vec3 calculateSpecularColor(in vec3 camera_pos, in vec3 frag_pos_world, in vec3 light_dir, in vec3 normals, in float specular_strength, in vec3 light_color) {
    vec3 view_dir = normalize(camera_pos - frag_pos_world);
    vec3 reflect_dir = reflect(-light_dir, normals);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 32);
    vec3 specular = specular_strength * spec * light_color;

    return(specular);
}