#ifndef POELITE_PRIMITIVE_ENTITY_FACTORY_HPP
#define POELITE_PRIMITIVE_ENTITY_FACTORY_HPP

#include "mesh/node.hpp"

class PrimitiveEntityFactory {
    Context& ctx;

    PrimitiveShape shape;
    bool is_static = false;

    std::shared_ptr<Renderable::ColoredPrimitive> generateRenderablePrimitive(Shader const& shader, Renderable::Node& base_node);

public:
    PrimitiveEntityFactory(Context& ctx);

    void setShape(PrimitiveShape shape);
    void isStatic(bool is_static);

    std::shared_ptr<Entity> make();
};

#endif
