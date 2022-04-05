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
        throw std::exception();
    }

    std::string line;
    while (std::getline(obj_file, line)) {
        std::istringstream line_stream(line);

        std::string type;
        line_stream >> type;
        if (type == "v") {
            float x, y, z;
            line_stream >> x >> y >> z;

            this->vertices.insert(this->vertices.end(), glm::vec3(x, y, z));
        } else if (type == "vt") {
            float x, y;
            line_stream >> x >> y;

            this->tex_vertices.insert(this->tex_vertices.end(), {x, y});
        } else if (type == "vn") {
            float x, y, z;
            line_stream >> x >> y >> z;

            this->vec_normals.insert(this->vec_normals.end(), {x, y, z});
        }
        else if (type == "f") {
            unsigned int face[10];
            unsigned int tex_face[10];
            unsigned int normals_face[10];

            int vert_count = 0;
            while (!line_stream.eof()) {
                std::string face_str;
                line_stream >> face_str;

                std::istringstream face_str_stream(face_str);

                std::string vert_corner;
                std::getline(face_str_stream, vert_corner, '/');
                unsigned int indice_vert_corner = std::stoul(vert_corner);
                face[vert_count] = indice_vert_corner;
                face[vert_count] -= 1;

                std::string tex_corner;
                std::getline(face_str_stream, tex_corner, '/');
                unsigned int indice_tex_corner = std::stoul(tex_corner);
                tex_face[vert_count] = indice_tex_corner;
                tex_face[vert_count] -= 1;

                std::string normal_corner;
                std::getline(face_str_stream, normal_corner, '/');
                unsigned int indice_normal_corner = std::stoul(normal_corner);
                normals_face[vert_count] = indice_normal_corner;
                normals_face[vert_count] -= 1;
                vert_count++;
            }
            //Insert vertice (x, y, z), tex_s, tex_t
            //
            
            glm::vec3* cur_face_vertices = new glm::vec3[vert_count];
            glm::vec2* cur_face_tex_vertices = new glm::vec2[vert_count];
            glm::vec3* cur_face_normals = new glm::vec3[vert_count];
            for (int i = 0; i < vert_count; ++i) {
                cur_face_vertices[i] = this->vertices[face[i]];
                cur_face_tex_vertices[i] = this->tex_vertices[tex_face[i]];
                cur_face_normals[i] = this->vec_normals[normals_face[i]];
            }
            std::vector<float> indiced_triangles;

            //First Triangle
            //[0]x, y, z, s, t
            //[1]x, y, z, s, t
            //[2]x, y, z, s, t
            //Second triangle
            //[0]--||--
            //[2]--||--
            //[3]--||--

            if (vert_count > 3) {
                for (int i = 0; i < 2; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (j < 1) {
                            indiced_triangles.insert(indiced_triangles.end(), {
                                    cur_face_vertices[0].x,
                                    cur_face_vertices[0].y,
                                    cur_face_vertices[0].z,
                                    cur_face_tex_vertices[0].x,
                                    cur_face_tex_vertices[0].y});
                        } else {
                            indiced_triangles.insert(indiced_triangles.end(), {
                                    cur_face_vertices[i + j].x,
                                    cur_face_vertices[i + j].y,
                                    cur_face_vertices[i + j].z,
                                    cur_face_tex_vertices[i + j].x,
                                    cur_face_tex_vertices[i + j].y});
                        }
                        this->total_vertices++;
                    }
                }
            } else {
                for (int j = 0; j < 3; ++j) {
                    if (j < 1) {
                        indiced_triangles.insert(indiced_triangles.end(), {
                                cur_face_vertices[0].x,
                                cur_face_vertices[0].y,
                                cur_face_vertices[0].z,
                                cur_face_tex_vertices[0].x,
                                cur_face_tex_vertices[0].y});
                    } else {
                        indiced_triangles.insert(indiced_triangles.end(), {
                                cur_face_vertices[j].x,
                                cur_face_vertices[j].y,
                                cur_face_vertices[j].z,
                                cur_face_tex_vertices[j].x,
                                cur_face_tex_vertices[j].y});
                    }
                    this->total_vertices++;
                }
            }



            this->triangles.insert(this->triangles.end(), indiced_triangles.begin(), indiced_triangles.end());
            delete[] cur_face_vertices;
            delete[] cur_face_tex_vertices;
            delete[] cur_face_normals;
        }
    }

    obj_file.close();
}
