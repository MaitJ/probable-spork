#ifndef PRIMITIVE_ENTITY_FACTORY_HPP
#define PRIMITIVE_ENTITY_FACTORY_HPP

#include "mesh/mesh_builder.hpp"
#include "renderables/mesh/node.hpp"

class PrimitiveEntityFactory {
    Context& ctx;

    bool is_static = false;
    MeshBuilder mesh_builder;

    std::vector<float> getShapeVertices(PrimitiveShape shape);

public:
    PrimitiveEntityFactory(Context& ctx);

    void setShape(PrimitiveShape shape);
    void isStatic(bool is_static);

    std::shared_ptr<Entity> make();
};

#endif
