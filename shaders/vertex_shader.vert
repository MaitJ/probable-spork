#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoordinates;

uniform mat4 MVP;

out vec2 tex_coords;
void main() {
    gl_Position = MVP * vec4(Position, 1.0f);
    tex_coords = TexCoordinates;
}
