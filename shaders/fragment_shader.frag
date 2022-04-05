#version 330 core

out vec4 FragColor;

in vec2 tex_coords;

uniform sampler2D tex;
uniform bool is_textured;

void main() {
    if (is_textured) {
        FragColor = texture(tex, tex_coords);
    } else {
        FragColor = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    }
}
