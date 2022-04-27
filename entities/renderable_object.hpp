#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "../shader.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "obj.hpp"

class Transform;
#include "../components/transform.hpp"

enum PrimitiveShape {
	PLANE
};

//Right handed coord system
class RenderableObject {
public:
	void render();
	RenderableObject(bool gen_buffers);
	RenderableObject(bool gen_buffers, Shader& shader);
	RenderableObject(std::string obj_file);
	RenderableObject(std::string obj_file, std::string tex_file);
    //Tee vec3 variandid ka
	void setScale(float x, float y, float z);
	void setPos(float x, float y, float z);
    void setOrientation(float x, float y, float z);
	void setScale(glm::vec3 const& scale);
	void setPos(glm::vec3 const& pos);
    void setOrientation(glm::vec3 const& orientation);
	void glBind();
    void genBuffers();

    void loadModel(std::string obj_file, std::string tex_file);
    void calcModel();

	Shader& shader;

	unsigned int total_vertices = 0;

    glm::mat4& view_proj;

private:
    void baseObjSetup(Utilities::Obj* obj);

private:
    bool textured = false;
    bool is_wireframe = false;
	unsigned int vbo, vao, ebo, to = 0;

    glm::mat4 model_mat = glm::mat4(1.0f);
	glm::mat4 scale_mat = glm::mat4(1.0f);
	glm::mat4 pos_mat = glm::mat4(1.0f);
    glm::quat orientation = glm::quat(1.0f, .0f, .0f, .0f);

    void loadTexture(std::string tex_file);

};

#endif // !RENDERABLE_ENTITY_H
