#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <utilities/types.hpp>
#include "../components/transform.hpp"
#include "wireframe.hpp"

class Context;

class Entity {

    bool is_visible = false;

public:
    int entity_id;
    Entity(int entity_id, Context const& ctx);
    Entity(Entity const& old_ent);

    void enableWireframe();
    void loadGLTFModel(const std::string file_name);
    Node& getRenderableObject();
    bool isVisible();

    Transform transform;
    Wireframe wireframe;
    Context const& ctx;
	Node renderable;
};

namespace PrimitiveObjects {

	template <PrimitiveShape>
	void loadPrimitive(Entity& ent);

	template <>
	void loadPrimitive<PLANE>(Entity& ent);

}
#endif // !ENTITY_H
