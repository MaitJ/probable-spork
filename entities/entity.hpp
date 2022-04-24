#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <utilities/types.hpp>
#include "renderable_object.hpp"
#include "../components/transform.hpp"

class Entity {
	RenderableObject renderable;
    bool is_visible = false;

public:
    Entity();
    Transform transform;

    void enableWireframe();
    void loadModel(const std::string obj_file, const std::string texture_file);
    RenderableObject& getRenderableObject();
    bool isVisible();

};

namespace PrimitiveObjects {

	template <PrimitiveShape>
	void loadPrimitive(Entity& ent);

	template <>
	void loadPrimitive<PLANE>(Entity& ent);
}
#endif // !ENTITY_H
