#include "vao.h"
#include <stdio.h>
VAO::VAO()
{
    // Generate a Vertex Array Object
    glGenVertexArrays(1, &m_id);
    printf("VAO id: %d\n", m_id);
}

void VAO::LinkAttrib(VBO& vbo, GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid* offset)
{
    // Bind the VBO
    vbo.Bind();
    // Link the VBO to the VAO
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
    // Enable the VBO
    glEnableVertexAttribArray(index);
    // // Unbind the VBO
    // vbo.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(m_id);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &m_id);
}
