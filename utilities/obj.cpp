#include <stdlib.h>
#include "obj.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace Utilities;

Obj::Obj(std::string obj_file_name) {
    std::ifstream obj_file(obj_file_name, std::ios::in);

    if (!obj_file) {
        std::cerr << "Failed to open .obj file" << std::endl;
        throw std::exception("Failed to open .obj file");
    }

    std::string line;
    while (std::getline(obj_file, line)) {
        std::istringstream line_stream(line);

        std::string type;
        line_stream >> type;
        if (type == "v") {
            float x, y, z;
            line_stream >> x >> y >> z;

            this->vertices.insert(this->vertices.end(), {x, y, z});
        } else if (type == "f") {
            unsigned int face[4];

            for (int i = 0; i < 4; ++i) {
                std::string indice;
                line_stream >> indice;
                std::istringstream indice_stream(indice);
                std::string indice_corner;
                std::getline(indice_stream, indice_corner, '/');

                face[i] = std::stoul(indice_corner);
                face[i] -= 1;
            }

            this->triangles.insert(this->triangles.end(), {face[0], face[1], face[2]});
            this->triangles.insert(this->triangles.end(), {face[0], face[2], face[3]});
        }
    }

    obj_file.close();
}
