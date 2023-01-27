#include <engine/mesh.h>
#include <engine/ebo.h>
#include <stdio.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Texture *texture)
{
    m_vertices = vertices;
    m_indices = indices;
    m_texture = texture;
    m_instancing = 1;
    Init(std::vector<glm::mat4>());
}
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Texture *texture, unsigned int instancing, std::vector<glm::mat4> instanceMatrix)
{
    m_vertices = vertices;
    m_indices = indices;
    m_texture = texture;
    m_instancing = instancing;

    Init(instanceMatrix);
}

void Mesh::Init(std::vector<glm::mat4> instanceMatrix)
{
    m_vao.Bind();
    VBO instanceVBO(instanceMatrix);
    VBO vbo(m_vertices);
    EBO ebo(m_indices);

    m_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (GLvoid *)offsetof(Vertex, position));
    m_vao.LinkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex), (GLvoid *)offsetof(Vertex, color));
    m_vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (GLvoid *)offsetof(Vertex, normal));
    m_vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texCoord));

    if (m_instancing != 1)
    {
        instanceVBO.Bind();
        m_vao.LinkAttrib(instanceVBO, 4, 4, GL_FLOAT, sizeof(glm::mat4), (GLvoid *)0);
        m_vao.LinkAttrib(instanceVBO, 5, 4, GL_FLOAT, sizeof(glm::mat4), (GLvoid *)sizeof(glm::vec4));
        m_vao.LinkAttrib(instanceVBO, 6, 4, GL_FLOAT, sizeof(glm::mat4), (GLvoid *)(sizeof(glm::vec4) * 2));
        m_vao.LinkAttrib(instanceVBO, 7, 4, GL_FLOAT, sizeof(glm::mat4), (GLvoid *)(sizeof(glm::vec4) * 3));

        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        glVertexAttribDivisor(7, 1);
    }

    m_vao.Unbind();
    vbo.Unbind();
    instanceVBO.Unbind();
    ebo.Unbind();
}

void Mesh::Draw()
{
    // shader.Bind();
    m_vao.Bind();
    // m_texture->Bind(GL_TEXTURE0);

    if (m_instancing == 1)
    {
        if (m_isPlane)
        {
            glDrawArrays(GL_PATCHES, 0, 3);
        }
        else
        {
            glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        }
    }
    else
    {
        glDrawElementsInstanced(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0, m_instancing);
    }
}