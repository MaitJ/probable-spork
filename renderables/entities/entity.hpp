#ifndef ENTITY_H
#define ENTITY_H

#include "glm/glm/glm.hpp"
#include "types.hpp"
#include "transform.hpp"
#include "renderables/wireframe.hpp"
#include "renderables/mesh/mesh.hpp"


class Context;


class Entity {

    bool is_visible = false;

public:
    int entity_id;
    Entity(int entity_id, Context const& ctx);
    Entity(Entity const& old_ent);

    void enableWireframe();
    Renderable::Mesh& getRenderableObject();
    bool isVisible();

    Transform transform;
    Wireframe wireframe;
    Context const& ctx;
	Renderable::Mesh mesh;
};

#endif // !ENTITY_H
