#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>

class Shader {
public:
    Shader(std::string vertex_shader_file, std::string fragment_shader_file);
    void use();
    void close();
    GLuint id;
private:
    const char* read_from_file(std::string file_name);
};

#endif
