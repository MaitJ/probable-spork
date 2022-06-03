#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "../shader.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "obj.hpp"

class Transform;
#include "../components/transform.hpp"
#include "gltf_loader.hpp"
#include "shaders/shader_manager.hpp"

enum PrimitiveShape {
	PLANE
};

//Right handed coord system
class Node {
public:
    Node();
    ~Node();
	void render();
	Node(ShaderManager& shader_manager, std::string shader_name);
	void setScale(float x, float y, float z);
	void setPos(float x, float y, float z);
    void setOrientation(float x, float y, float z);
	void setScale(glm::vec3 const& scale);
	void setPos(glm::vec3 const& pos);
    void setOrientation(glm::vec3 const& orientation);
	void glBind() const;
    void genBuffers();

    void loadGLTFModel(const std::string& file_name);
    void calcModel();

	Shader const* shader;

	//unsigned int total_vertices = 0;
    std::vector<unsigned int> total_vertices;

    glm::mat4& view_proj;

    unsigned int* tos = nullptr;
    int texture_count = 0;

    int primitives_count;
    unsigned int* primitive_offsets = nullptr;

    bool is_wireframe = false;
private:
    bool textured = false;
    unsigned int vbo, vao, ebo;


    glm::mat4 model_mat = glm::mat4(1.0f);
	glm::mat4 scale_mat = glm::mat4(1.0f);
	glm::mat4 pos_mat = glm::mat4(1.0f);
    glm::quat orientation = glm::quat(1.0f, .0f, .0f, .0f);

    void loadGLTFTexture(int i, const Mesh &mesh);
};

#endif // !RENDERABLE_ENTITY_H
