#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <utilities/types.hpp>
#include "renderable_object.hpp"

class Entity {
public:
	glm::vec3 position;
	Dimensions dimensions;

	
	RenderableObject* renderable_object;

};

#endif // !ENTITY_H
