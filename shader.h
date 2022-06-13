#ifndef SHADER_H
#define SHADER_H

#include "gl.h"
#include <glm/glm.hpp>

class Shader
{
private:
    GLuint m_program;

public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~Shader();

    void Bind();
    void Unbind();
    void SetUniform(const char* name, float value);
    void SetUniform(const char* name, int value);
    void SetUniform(const char* name, const glm::vec2& value);
    void SetUniform(const char* name, const glm::vec3& value);
    void SetUniform(const char* name, const glm::mat4& value);
};

#endif // SHADER_H