#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>


class Shader {
public:
    Shader();
    Shader(std::string vertex_shader_file, std::string fragment_shader_file);
    void unbind() const;
    void use() const;
    void close() const;
    void setMatrix4f(std::string uniform_loc, glm::mat4 mat);
    void setVec3f(std::string uniform_loc, glm::vec3 vec);

    void loadAndCompile(const std::string vertex_shader_file, const std::string fragment_shader_file);
    GLuint id;

    int layout_len = 0;

private:
    const char* read_from_file(std::string file_name);

};

namespace MainShaders{
    Shader const& getWfShader();
    Shader const& getDefaultShader();
    Shader* loadWfShader();
    Shader* loadDefaultShader();
}

#endif
