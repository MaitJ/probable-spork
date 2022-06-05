#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 aNormals;

uniform mat4 MVP;
uniform mat4 Model;
uniform mat3 normal_mat;

out vec3 Normals;
out vec3 frag_pos_world;

void main() {
    gl_Position = MVP * vec4(Position, 1.0f);
    frag_pos_world = vec3(Model * vec4(Position, 1.0f));
    Normals = normal_mat * aNormals;
}
