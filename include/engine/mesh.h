#ifndef MESH_H
#define MESH_H
// inspired by https://www.youtube.com/watch?v=NUZF_5RKfS4
#include <engine/gl.h>
#include <vector>
#include <glm/glm.hpp>
#include <engine/shader.h>
#include <engine/vbo.h>
#include <engine/vao.h>
#include <engine/texture.h>


class Mesh
{
    private:
        std::vector<Vertex> m_vertices;
        std::vector<GLuint> m_indices;
        unsigned int m_instancing;
        
        Texture* m_texture;
        VAO m_vao;
        bool m_isPlane = false;
    public:
        void Init(std::vector<glm::mat4> instanceMatrix);

    public:
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Texture* texture);
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Texture* texture, unsigned int instancing, std::vector<glm::mat4> instanceMatrix);
        void Draw();
        
        void SetIsPlane(bool isPlane) { m_isPlane = isPlane; }
};
#endif // MESH_H