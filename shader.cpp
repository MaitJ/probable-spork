#include <stdlib.h>
#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VERTEX_SHADER_FILE "vertex_shader.vert"
#define FRAGMENT_SHADER_FILE "fragment_shader_mod.frag"
#define WF_VERTEX_SHADER_FILE "wf_vertex_shader.vert"
#define WF_FRAGMENT_SHADER_FILE "wf_fragment_shader.frag"
#define LIGHTNING_CALCULATIONS_SHADER "lightning_calculations.glsl"

Shader::Shader(std::string vertex_shader_file, std::string fragment_shader_file, std::string name) {
    this->loadAndCompile(vertex_shader_file, fragment_shader_file, name);
}

Shader::Shader() {}

void Shader::loadAndCompile(const std::string vertex_shader_file, const std::string fragment_shader_file, std::string name) {

    this->name = name;

    const char* vertex_shader_text = Shader::read_from_file("shaders/" + vertex_shader_file);
    const char* fragment_shader_text = Shader::read_from_file("shaders/" + fragment_shader_file);

    unsigned int vertex_shader, fragment_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "Vertex shader name: " << vertex_shader_file << "\n";
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    std::string lightning_calculations_string(LIGHTNING_CALCULATIONS_SHADER);
    const char* lightning_calculations_text = Shader::read_from_file("shaders/" + lightning_calculations_string);

    const char* fragment_shader_compiled[2] = {lightning_calculations_text, fragment_shader_text };

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 2, fragment_shader_compiled, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cout << "Fragment shader name: " << fragment_shader_file << "\n";
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
 
    this->id = glCreateProgram();
    glAttachShader(this->id, vertex_shader);
    glAttachShader(this->id, fragment_shader);
    glLinkProgram(this->id);

    delete[] vertex_shader_text;
    delete[] fragment_shader_text;

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}


void Shader::use() const {
    glUseProgram(this->id);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::close() const {
    glDeleteProgram(this->id);
}

void Shader::setMatrix4f(std::string uniform_loc, glm::mat4 mat) {
    this->use();
    int uniform_location = glGetUniformLocation(this->id, uniform_loc.c_str());
    glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(mat));
    this->unbind();
}

void Shader::setVec3f(std::string uniform_loc, glm::vec3 vec) {
    this->use();
    int uniform_location = glGetUniformLocation(this->id, uniform_loc.c_str());
    glUniform3fv(uniform_location, 1, glm::value_ptr(vec));
    this->unbind();
}


const char* Shader::read_from_file(std::string file_name) {
    std::ifstream shader_file(file_name);

    if (!shader_file) {
        std::cerr << "Error opening shader file" << std::endl;
        throw new std::exception();
    }

    shader_file.seekg(0, shader_file.end);
    int file_length = shader_file.tellg();
    shader_file.seekg(0, shader_file.beg);

    char* file_content = new char[file_length + (long long)1];
    shader_file.read(file_content, file_length);
    file_content[file_length] = '\0';
    shader_file.close();

    return file_content;
}
