#ifndef OBJ_H
#define OBJ_H
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Utilities {

	class Obj {
	public:
		Obj(std::string obj_file_name);
	public:
		std::vector<float> vertices;
		std::vector<unsigned int> triangles;
	};
}



#endif
