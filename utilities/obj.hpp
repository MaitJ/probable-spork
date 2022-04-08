#ifndef OBJ_H
#define OBJ_H
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Utilities {

	class Obj {
        void createTriangle(std::vector<float>& container, int indice, glm::vec3* vertices, glm::vec2* tex_vertices, glm::vec3* normals);
	public:
		Obj(std::string obj_file_name);
	public:
        unsigned int total_vertices = 0;
		std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> tex_vertices;
        std::vector<glm::vec3> vec_normals;
		std::vector<float> triangles;
	};
}



#endif
