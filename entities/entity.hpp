#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <utilities/types.hpp>
#include "renderable_object.hpp"
#include "../components/transform.hpp"
#include "wireframe.hpp"

class Entity {
    static int entity_count;

    int entity_id;

    bool is_visible = false;
    bool is_wireframed = false;
    Wireframe wireframe;

public:
    Entity();
    //This should be objects own transform/collisions
    Transform transform;
	RenderableObject renderable;

    void enableWireframe();
    void enableCollisions();
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
