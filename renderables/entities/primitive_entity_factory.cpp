#include "entities/entity.hpp"
#include "renderable_manager.hpp"
#include "primitive_entity_factory.hpp"
#include "mesh/primitive/colored_primitive.hpp"

PrimitiveEntityFactory::PrimitiveEntityFactory(Context &ctx) : ctx(ctx) {
    Shader const& colored_shader = ShaderManager::getShader("colored");
    mesh_builder.setShader(colored_shader);
}

void PrimitiveEntityFactory::setShape(PrimitiveShape shape) {
    std::vector<float> primitive_vertices = getShapeVertices(shape);
    mesh_builder.addPrimitive<Renderable::ColoredPrimitive>(primitive_vertices, 6);
}

void PrimitiveEntityFactory::isStatic(bool is_static) { this->is_static = is_static;}

std::shared_ptr<Entity> PrimitiveEntityFactory::make() {
    std::shared_ptr<Entity> object_entity = !is_static ? ctx.createEntity().lock() : ctx.createStaticEntity().lock();
    object_entity->mesh = mesh_builder.build();
    RenderableManager::addRenderableMesh(&object_entity->mesh);
    return object_entity;
}

std::vector<float> PrimitiveEntityFactory::getShapeVertices(PrimitiveShape shape) {
    switch (shape) {
        case PrimitiveShape::PLANE: {
            return {
                    -1.0f, 0.0f, 1.0f, .0f, 1.0f, .0f,
                    1.0f, 0.0f, 1.0f,  .0f, 1.0f, .0f,
                    1.0f, 0.0f, -1.0f,  .0f, 1.0f, .0f,

                    -1.0f, 0.0f, 1.0f,  .0f, 1.0f, .0f,
                    -1.0f, 0.0f, -1.0f,  .0f, 1.0f, .0f,
                    1.0f, 0.0f, -1.0f,  .0f, 1.0f, .0f
            };
        }
        case PrimitiveShape::CUBE: {
            return {
                    //Front triangles
                    -1.f, -1.0f, 1.f, 0.0f, 1.0f, .0f,
                    1.f,  -1.0f, 1.f, 0.0f, 1.0f, .0f,
                    -1.f,  1.0f, 1.f, 0.0f, 1.0f, .0f,
                    1.f,  -1.0f, 1.f, 0.0f, 1.0f, .0f,
                    1.f,   1.0f, 1.f, 0.0f, 1.0f, .0f,
                    -1.f,  1.0f, 1.f, 0.0f, 1.0f, .0f,

                    //Back triangles
                    -1.f, -1.0f, -1.f, 0.0f, 1.0f, .0f,
                    1.f,  -1.0f, -1.f, 0.0f, 1.0f, .0f,
                    -1.f,  1.0f, -1.f, 0.0f, 1.0f, .0f,
                    1.f,  -1.0f, -1.f, 0.0f, 1.0f, .0f,
                    1.f,   1.0f, -1.f, 0.0f, 1.0f, .0f,
                    -1.f,  1.0f, -1.f, 0.0f, 1.0f, .0f,

                    //Left side
                    -1.f,  -1.0f, 1.f, 0.0f, 1.0f, .0f,
                    -1.f, -1.0f, -1.f, 0.0f, 1.0f, .0f,
                    -1.f,   1.0f, 1.f, 0.0f, 1.0f, .0f,
                    -1.f, -1.0f, -1.f, 0.0f, 1.0f, .0f,
                    -1.f,  1.0f, -1.f, 0.0f, 1.0f, .0f,
                    -1.f,   1.0f, 1.f, 0.0f, 1.0f, .0f,

                    //Right side
                    1.f,  -1.0f, 1.f, 0.0f, 1.0f, .0f,
                    1.f, -1.0f, -1.f, 0.0f, 1.0f, .0f,
                    1.f,   1.0f, 1.f, 0.0f, 1.0f, .0f,
                    1.f, -1.0f, -1.f, 0.0f, 1.0f, .0f,
                    1.f,  1.0f, -1.f, 0.0f, 1.0f, .0f,
                    1.f,   1.0f, 1.f, 0.0f, 1.0f, .0f,

                    -1.f,  1.f, 1.f, 0.0f, 1.0f, .0f,
                    1.f, 1.0f, 1.f, 0.0f, 1.0f, .0f,
                    1.f,   1.0f, -1.f, 0.0f, 1.0f, .0f,
                    1.f, 1.0f, -1.f, 0.0f, 1.0f, .0f,
                    -1.f,  1.0f, -1.f, 0.0f, 1.0f, .0f,
                    -1.f,   1.0f, 1.f, 0.0f, 1.0f, .0f,

                    -1.f,  -1.f, 1.f, 0.0f, 1.0f, .0f,
                    1.f, -1.0f, 1.f, 0.0f, 1.0f, .0f,
                    1.f,   -1.0f, -1.f, 0.0f, 1.0f, .0f,
                    1.f, -1.0f, -1.f, 0.0f, 1.0f, .0f,
                    -1.f,  -1.0f, -1.f, 0.0f, 1.0f, .0f,
                    -1.f,   -1.0f, 1.f, 0.0f, 1.0f, .0f,

            };
        }
    }
    return std::vector<float>();
}
