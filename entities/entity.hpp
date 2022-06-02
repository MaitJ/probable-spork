#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <utilities/types.hpp>
#include "node.hpp"
#include "../components/transform.hpp"
#include "wireframe.hpp"

class Context;

class Entity {

    bool is_visible = false;
    bool is_wireframed = false;

public:
    int entity_id;
    Entity(int entity_id, Context const& ctx);
    Entity(Entity const& old_ent);
    //Physics use this transform
    Transform transform;
    Wireframe wireframe;
    //Renderer uses this for scale/rot etcetera
	Node renderable;

    Context const& ctx;

    void enableWireframe();

    /*Excluded because there's a better way
    void enableCollisions();
     */
    void loadModel(const std::string obj_file, const std::string texture_file);
    Node& getRenderableObject();
    bool isVisible();

};

namespace PrimitiveObjects {

	template <PrimitiveShape>
	void loadPrimitive(Entity& ent);

	template <>
	void loadPrimitive<PLANE>(Entity& ent);

}
#endif // !ENTITY_H
