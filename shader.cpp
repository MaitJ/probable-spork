#include <stdlib.h>
#include "shader.hpp"
#include <fstream>
#include <iostream>

Shader::Shader(std::string vertex_shader_file, std::string fragment_shader_file) {

    const char* vertex_shader_text = Shader::read_from_file("shaders/vertex_shader.vert");
    const char* fragment_shader_text = Shader::read_from_file("shaders/fragment_shader.frag");

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
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
 
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
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


void Shader::use() {
    glUseProgram(this->id);
}

void Shader::close() {
    glDeleteProgram(this->id);
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
