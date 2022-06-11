#include "mesh.h"
#include "ebo.h"
#include <stdio.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
    m_vertices = vertices;
    m_indices = indices;

    Init();
}

Mesh::Mesh(Vertex vertices[], std::vector<GLuint> indices)
{
    m_vertices.assign(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    m_indices = indices;

    Init();
}

void Mesh::Init()
{
    m_vao.Bind();

    VBO vbo(m_vertices);
    EBO ebo(m_indices);
    
    m_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    m_vao.LinkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    m_vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

    vbo.Bind();

    

    m_vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
    m_vao.Bind();
    // check what vbo is bound
    GLint i;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &i);
    printf("VBO ID: %d\n", i);
}

void Mesh::Draw(Shader& shader, const glm::mat4& viewProjectionMatrix)
{
    shader.Bind();
    m_vao.Bind();
    shader.SetUniform("u_viewProjection", viewProjectionMatrix);
    // check what vbo is bound
    // GLint i;
    // glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &i);
    // printf("VBO ID: %d\n", i);
    // make sure glDrawElements will not segment fault
    printf("m_indices.size(): %d\n", m_indices.size());
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}