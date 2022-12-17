#include "mesh_builder.hpp"
#include "logger.hpp"

MeshBuilder::~MeshBuilder() {
    if (shader != nullptr) delete shader;
}

MeshBuilder& MeshBuilder::setShader(Shader const& shader) {
    this->shader = new Shader(shader);
    return *this;
}

Renderable::Mesh MeshBuilder::build() {
    if (primitives.size() < 1) {
        Logger::warn("Please specify primitives in MeshBuilder");
        return Renderable::Mesh();
    }

    if (shader == nullptr) {
        Logger::warn("Please specify shader in MeshBuilder");
        return Renderable::Mesh();
    }

    Renderable::Mesh mesh;
    Renderable::Node base_node;

    std::for_each(primitives.begin(), primitives.end(), [&base_node](auto& primitive) {
        base_node.primitives.push_back(primitive);
    });

    mesh.nodes.push_back(base_node);
    return mesh;
}

