#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "../shader.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "obj.hpp"

enum PrimitiveShape {
	PLANE
};

//Right handed coord system
class RenderableObject {
public:
	void render();
	RenderableObject();
	RenderableObject(std::string obj_file, glm::mat4* view_proj, Shader* shader);
	RenderableObject(std::string obj_file, std::string tex_file, glm::mat4* view_proj, Shader* shader);
	void setScale(float x, float y, float z);
	void setPos(float x, float y, float z);
    void setOrientation(float x, float y, float z);
	void glBind();

    void calcModel();

	Shader* shader = nullptr;

	unsigned int total_vertices = 0;

    glm::mat4* view_proj = nullptr;

private:
    void baseObjSetup(Utilities::Obj* obj);

private:
    bool textured = false;
    //Vertex buffer, vertex array, element array, texture object
	unsigned int vbo, vao, ebo, to = 0;

    glm::mat4 model_mat = glm::mat4(1.0f);
	glm::mat4 scale_mat = glm::mat4(1.0f);
	glm::mat4 pos_mat = glm::mat4(1.0f);
    glm::quat orientation = glm::quat(1.0f, .0f, .0f, .0f);

};

namespace Renderables {

	template <PrimitiveShape>
	RenderableObject Primitive(glm::mat4* view_proj);

	template <>
	RenderableObject Primitive<PLANE>(glm::mat4* view_proj);
}

#endif // !RENDERABLE_ENTITY_H
