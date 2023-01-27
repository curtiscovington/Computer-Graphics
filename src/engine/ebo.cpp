#include <engine/ebo.h>

EBO::EBO(std::vector<GLuint>& indices)
{
    // Generate a Element Buffer Object
    glGenBuffers(1, &m_id);
    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    // Upload the data to the GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
    glDeleteBuffers(1, &m_id);
}