#include "model.h"
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
Model::Model(glm::vec3 position, glm::vec3 rotation, Texture* texture, Shader* shader, std::vector<Mesh*> meshes)
{
    m_position = position;
    m_rotation = rotation;
    m_texture = texture;
    m_shader = shader;
    m_meshes = meshes;
}

Model::Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Texture* texture, Shader* shader, std::vector<Mesh*> meshes)
{
    m_position = position;
    m_rotation = rotation;
    m_texture = texture;
    m_shader = shader;
    m_meshes = meshes;
    m_scale = scale;
}

void Model::Draw(const glm::mat4& viewProjectionMatrix)
{   
    
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, m_position);
    // translate by half a unit to make the model center at the origin
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    // translate back to the original position
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, -0.5f, -0.5f));
    modelMatrix = glm::scale(modelMatrix, m_scale);
    m_shader->Bind();
    m_texture->Bind(GL_TEXTURE0);
    m_shader->SetUniform("u_modelMatrix", modelMatrix);
    m_shader->SetUniform("u_viewProjection", viewProjectionMatrix);
    m_shader->SetUniform("u_gSampler", 0);
    for (Mesh* mesh : m_meshes)
    {
        
        mesh->Draw(*m_shader, viewProjectionMatrix);
    }
}