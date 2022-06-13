#ifndef MODEL_H
#define MODEL_H

#include "gl.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include <vector>
#include <glm/glm.hpp>

class Model
{
    private:
        Texture* m_texture;
        std::vector<Mesh*> m_meshes;
        Shader* m_shader;
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale = glm::vec3(1.0f);

    public:
        Model(glm::vec3 position, glm::vec3 rotation, Texture* texture, Shader* shader, std::vector<Mesh*> meshes);
        Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Texture* texture, Shader* shader, std::vector<Mesh*> meshes);

        void Draw(const glm::mat4& viewProjectionMatrix);
};

#endif // MODEL_H