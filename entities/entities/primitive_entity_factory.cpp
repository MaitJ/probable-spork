#include "entity.hpp"
#include "primitive_entity_factory.hpp"
#include "entities/renderable_manager.hpp"
#include "mesh/primitive/colored_primitive.hpp"

PrimitiveEntityFactory::PrimitiveEntityFactory(Context &ctx) : ctx(ctx) {}

void PrimitiveEntityFactory::setShape(PrimitiveShape shape) { this->shape = shape; }
void PrimitiveEntityFactory::isStatic(bool is_static) { this->is_static = is_static;}

std::shared_ptr<Entity> PrimitiveEntityFactory::make() {
    std::shared_ptr<Entity> object_entity = !is_static ? ctx.createEntity().lock() : ctx.createStaticEntity().lock();
    Renderable::Mesh& ent_renderable = object_entity->getRenderableObject();
    Shader const& colored_shader = ShaderManager::getShader("colored");
    Renderable::Node base_node;

    auto primitive_ptr =  generateRenderablePrimitive(colored_shader, base_node);

    base_node.primitives.push_back(primitive_ptr);
    ent_renderable.nodes.push_back(base_node);

    RenderableManager::addRenderableMesh(&ent_renderable);

    return object_entity;
}

std::shared_ptr<Renderable::ColoredPrimitive> PrimitiveEntityFactory::generateRenderablePrimitive(Shader const& shader, Renderable::Node& base_node) {
    auto primitive = std::make_shared<Renderable::ColoredPrimitive>(shader);
    primitive->genGlBuffers();
    primitive->bindBuffers();

    switch (shape) {
        case PrimitiveShape::PLANE: {
            std::vector<float> plane_vertices = {
                    -1.0f, 0.0f, 1.0f, .0f, 1.0f, .0f,
                    1.0f, 0.0f, 1.0f,  .0f, 1.0f, .0f,
                    1.0f, 0.0f, -1.0f,  .0f, 1.0f, .0f,

                    -1.0f, 0.0f, 1.0f,  .0f, 1.0f, .0f,
                    -1.0f, 0.0f, -1.0f,  .0f, 1.0f, .0f,
                    1.0f, 0.0f, -1.0f,  .0f, 1.0f, .0f
            };

            primitive->loadPrimitive(plane_vertices, 6);
        }
        case PrimitiveShape::CUBE: {
            std::vector<float> cube_vertices = {
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
            };

            primitive->loadPrimitive(cube_vertices, cube_vertices.size() / 6);

        }
    }

    primitive->loadColor(glm::vec4(.9f, .9f, .9f, 1.f));
    return primitive;
}