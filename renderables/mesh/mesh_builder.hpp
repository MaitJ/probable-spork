#ifndef MESH_BUILDER_HPP
#define MESH_BUILDER_HPP


#include "mesh.hpp"

class MeshBuilder {
    std::vector<std::shared_ptr<Renderable::Primitive>> primitives;
    Shader const* shader = nullptr;

public:
    template<class PrimitiveType>
    MeshBuilder& addPrimitive(std::vector<float> const& primitive_vertices, int layout_length);
    MeshBuilder& setShader(Shader const& shader);
    Renderable::Mesh build();
};

#endif