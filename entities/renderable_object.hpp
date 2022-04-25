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
	RenderableObject();
	RenderableObject(std::string obj_file);
	RenderableObject(std::string obj_file, std::string tex_file);
	void setScale(float x, float y, float z);
	void setPos(float x, float y, float z);
    void setOrientation(float x, float y, float z);
	void glBind();

    void loadModel(std::string obj_file, std::string tex_file);
    void calcModel();

	Shader const& shader;
    Shader const& wf_shader;

	unsigned int total_vertices = 0;

    glm::mat4& view_proj;


    //Make a separate wireframe class
    RenderableObject wireframe;
    bool is_wireframe_enabled = false;
    void enableWireframe();

private:
    void baseObjSetup(Utilities::Obj* obj);

private:
    bool textured = false;
    //Vertex buffer, vertex array, element array, texture object
	unsigned int vbo, vao, ebo, to = 0;
    //Wireframe buffers
	unsigned int wf_vbo, wf_vao = 0;

    glm::mat4 model_mat = glm::mat4(1.0f);
	glm::mat4 scale_mat = glm::mat4(1.0f);
	glm::mat4 pos_mat = glm::mat4(1.0f);
    glm::quat orientation = glm::quat(1.0f, .0f, .0f, .0f);

    void loadTexture(std::string tex_file);

};

#endif // !RENDERABLE_ENTITY_H
