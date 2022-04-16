#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader();
    Shader(std::string vertex_shader_file, std::string fragment_shader_file);
    void unbind();
    void use();
    void close();
    void setMatrix4f(std::string uniform_loc, glm::mat4 mat);
    void setVec3f(std::string uniform_loc, glm::vec3 vec);

    GLuint id;

    int layout_len = 0;
private:
    const char* read_from_file(std::string file_name);

};

#endif
