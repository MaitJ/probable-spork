#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <utilities/types.hpp>
#include "renderable_object.hpp"
#include "../components/transform.hpp"

class Entity {
	RenderableObject* renderable = nullptr;
    bool is_visible = false;

public:
    Entity();
    ~Entity();
    Transform transform;

    void attachRenderable(RenderableObject* renderable);
    bool isVisible();
};

#endif // !ENTITY_H
