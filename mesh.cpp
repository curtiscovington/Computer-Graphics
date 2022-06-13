#include "mesh.h"
#include "ebo.h"
#include <stdio.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Texture* texture)
{
    m_vertices = vertices;
    m_indices = indices;
    m_texture = texture;
    Init();
}

void Mesh::Init()
{
    m_vao.Bind();
    VBO vbo(m_vertices);
    EBO ebo(m_indices);
    // VBO vbo(m_vertices);
    // EBO ebo(m_indices);
    
    m_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    m_vao.LinkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    m_vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    m_vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));

    

    m_vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Mesh::Draw(Shader& shader, const glm::mat4& viewProjectionMatrix)
{
    // shader.Bind();
    m_vao.Bind();
    // m_texture->Bind(GL_TEXTURE0);
    
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}