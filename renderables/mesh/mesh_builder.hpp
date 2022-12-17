#ifndef MESH_BUILDER_HPP
#define MESH_BUILDER_HPP


#include "mesh.hpp"

class MeshBuilder {
    std::vector<std::shared_ptr<Renderable::Primitive>> primitives;
    Shader const* shader = nullptr;

public:
    ~MeshBuilder();

    template<class PrimitiveType>

    MeshBuilder& addPrimitive(std::vector<float> const& primitive_vertices, int layout_length) {
        auto primitive = std::make_shared<PrimitiveType>(*shader);
        primitive->genGlBuffers();
        primitive->bindBuffers();

        primitive->loadPrimitive(primitive_vertices, primitive_vertices.size() / layout_length);
        primitive->loadColor(glm::vec4(.9f, .9f, .9f, 1.f));
        primitives.push_back(primitive);
        return *this;
    }

    MeshBuilder& setShader(Shader const& shader);
    Renderable::Mesh build();
};

#endif