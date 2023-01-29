#ifndef MODEL_H
#define MODEL_H

#include <engine/gl.h>
#include <engine/mesh.h>
#include <engine/texture.h>
#include <engine/shader.h>
#include <vector>
#include <glm/glm.hpp>

class Model
{
    private:
        Texture* m_texture;
        Texture* m_normalMap;
        std::vector<Mesh*> m_meshes;
        Shader* m_shader;
        bool m_visible = true;
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale = glm::vec3(1.0f);

    public:
        Model(glm::vec3 position, glm::vec3 rotation, Texture* texture, Texture* normalMap, Shader* shader, std::vector<Mesh*> meshes);
        Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Texture* texture, Texture* normalMap, Shader* shader, std::vector<Mesh*> meshes);

        void Draw(const glm::mat4& viewProjectionMatrix);
        void SetScale(glm::vec3 scale);
        void SetPosition(glm::vec3 position);
        void SetRotation(glm::vec3 rotation);
        void SetShader(Shader* shader) { m_shader = shader; }
        void Rotate(glm::vec3 rotation);

        void ToggleVisibility() { m_visible = !m_visible; }
};

#endif // MODEL_H