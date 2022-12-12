#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>


class Shader {
public:
    Shader();
    Shader(std::string vertex_shader_file, std::string fragment_shader_file, std::string name);
    void unbind() const;
    void use() const;
    void close() const;
    void setMatrix4f(std::string uniform_loc, glm::mat4 mat);
    void setVec3f(std::string uniform_loc, glm::vec3 vec);

    void loadAndCompile(const std::string vertex_shader_file, const std::string fragment_shader_file, std::string name);
    GLuint id = -1;

    int layout_len = 0;

    std::string name;

private:
    std::string read_from_file(std::string file_name);

};

#endif
