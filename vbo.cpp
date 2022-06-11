#include "vbo.h"
#include <stdio.h>
VBO::VBO(std::vector<Vertex>& vertices)
{
    // Generate a Vertex Buffer Object
    glGenBuffers(1, &m_id);
    printf("VBO ID: %d\n", m_id);
    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    // Upload the data to the GPU
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
    glDeleteBuffers(1, &m_id);
}