#include "shader.h"
#include <string>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

// reads the contents of a file into a string
static std::string readFile(const char* path) {
    printf("Reading file: %s\n", path);
    std::ifstream file(path);
    std::string contents;
    std::string line;
    while (std::getline(file, line)) {
        contents.append(line);
        contents.append("\n");
    }

    printf(contents.c_str());
    return contents;
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    // get the contents of the files
    std::string vertSource = readFile(vertexShaderPath);
    std::string fragSource = readFile(fragmentShaderPath);

    printf("vertSource: %s\n", vertSource.c_str());
    printf("fragSource: %s\n", fragSource.c_str());
    // create the shaders
    auto m_vertShader = glCreateShader(GL_VERTEX_SHADER);
    auto m_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    // compile the shaders
    const char* vertSourceCStr = vertSource.c_str();
    const char* fragSourceCStr = fragSource.c_str();
    glShaderSource(m_vertShader, 1, &vertSourceCStr, NULL);
    glCompileShader(m_vertShader);
    glShaderSource(m_fragShader, 1, &fragSourceCStr, NULL);
    glCompileShader(m_fragShader);
    // create the program
    m_program = glCreateProgram();
    glAttachShader(m_program, m_vertShader);
    glAttachShader(m_program, m_fragShader);
    glLinkProgram(m_program);
    // check for errors
    int success;
    char infoLog[512];
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        printf("Error linking program: %s\n", infoLog);
        exit(1);
    }
    glGetShaderiv(m_vertShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_vertShader, 512, NULL, infoLog);
        printf("Error compiling vertex shader: %s\n", infoLog);
        exit(1);
    }
    glGetShaderiv(m_fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_fragShader, 512, NULL, infoLog);
        printf("Error compiling fragment shader: %s\n", infoLog);
        exit(1);
    }
    // delete the shaders as the program now owns them
    glDeleteShader(m_vertShader);
    glDeleteShader(m_fragShader);
}

Shader::~Shader() {
    glDeleteProgram(m_program);
}

void Shader::Bind() {
    glUseProgram(m_program);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SetUniform(const char* name, float value) {
    glUniform1f(glGetUniformLocation(m_program, name), value);
}

void Shader::SetUniform(const char* name, int value) {
    glUniform1i(glGetUniformLocation(m_program, name), value);
}

void Shader::SetUniform(const char* name, const glm::vec2& value) {
    glUniform2f(glGetUniformLocation(m_program, name), value.x, value.y);
}

void Shader::SetUniform(const char* name, const glm::vec3& value) {
    glUniform3f(glGetUniformLocation(m_program, name), value.x, value.y, value.z);
}

void Shader::SetUniform(const char* name, const glm::mat4& value) {
    glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, GL_FALSE, glm::value_ptr(value));
}
