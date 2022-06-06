#include "mesh.hpp"
#include <vector>

Renderable::ColoredPrimitive::ColoredPrimitive(const Shader &shader) : shader(shader) {}

void Renderable::ColoredPrimitive::genGlBuffers() {
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
}

void Renderable::ColoredPrimitive::bindBuffers() {
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}


std::vector<float> Renderable::ColoredPrimitive::assembleVertices(std::vector<glm::vec3> positions,
                                                    std::vector<glm::vec3> normals,
                                                    std::vector<unsigned int> indices) {
    std::vector<float> vertex_data;

    for (unsigned int mesh_index : indices) {
        vertex_data.insert(vertex_data.end(), {positions[mesh_index][0], positions[mesh_index][1], positions[mesh_index][2]});
        vertex_data.insert(vertex_data.end(), {normals[mesh_index][0], normals[mesh_index][1], normals[mesh_index][2]});
    };

    return vertex_data;

}

void Renderable::ColoredPrimitive::loadPrimitive(std::vector<glm::vec3> positions,
                                                 std::vector<glm::vec3> normals,
                                                 std::vector<unsigned int> indices) {

    std::vector<float> vertex_data = this->assembleVertices(positions, normals, indices);
    this->vertices = indices.size();

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

}

void Renderable::ColoredPrimitive::loadMaterial(tinygltf::Material const& material) {
    std::vector<double> color = material.pbrMetallicRoughness.baseColorFactor;
    this->color = glm::vec4(color[0], color[1], color[2], color[3]);
}

void Renderable::ColoredPrimitive::render(glm::mat4 TRS) {

}

Renderable::TexturedPrimitive::TexturedPrimitive(const Shader &shader) : shader(shader) {}

void Renderable::TexturedPrimitive::bindBuffers() {
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindTexture(GL_TEXTURE_2D, this->to);
}

void Renderable::TexturedPrimitive::genGlBuffers() {
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->to);
}

std::vector<float> Renderable::TexturedPrimitive::assembleVertices(std::vector<glm::vec3> positions,
                                                                   std::vector<glm::vec3> normals,
                                                                   std::vector<glm::vec2> tex_coords,
                                                                   std::vector<unsigned int> indices) {
    std::vector<float> vertex_data;

    for (unsigned int mesh_index : indices) {
        vertex_data.insert(vertex_data.end(), {positions[mesh_index][0], positions[mesh_index][1], positions[mesh_index][2]});
        vertex_data.insert(vertex_data.end(), {tex_coords[mesh_index][0], tex_coords[mesh_index][1]});
        vertex_data.insert(vertex_data.end(), {normals[mesh_index][0], normals[mesh_index][1], normals[mesh_index][2]});
    };

    return vertex_data;

}

void Renderable::TexturedPrimitive::loadPrimitive(std::vector<glm::vec3> positions,
                                                  std::vector<glm::vec3> normals,
                                                  std::vector<glm::vec2> tex_coords,
                                                  std::vector<unsigned int> indices) {

    std::vector<float> vertex_data = this->assembleVertices(positions, normals, tex_coords, indices);
    this->vertices = indices.size();

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

}
