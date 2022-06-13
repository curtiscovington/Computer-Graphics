#ifndef MESH_H
#define MESH_H
// inspired by https://www.youtube.com/watch?v=NUZF_5RKfS4
#include "gl.h"
#include <vector>
#include <glm/glm.hpp>
#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "texture.h"


class Mesh
{
    private:
        std::vector<Vertex> m_vertices;
        std::vector<GLuint> m_indices;
        Texture* m_texture;
        VAO m_vao;


        void Init();

    public:
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Texture* texture);
        void Draw(Shader& shader, const glm::mat4& viewProjectionMatrix);
};
#endif // MESH_H