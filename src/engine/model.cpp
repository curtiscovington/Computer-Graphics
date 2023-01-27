#include <engine/model.h>
#include <engine/camera.h>
#include <glm/gtc/matrix_transform.hpp>
Model::Model(glm::vec3 position, glm::vec3 rotation, Texture* texture, Texture* normalMap, Shader* shader, std::vector<Mesh*> meshes)
{
    m_position = position;
    m_rotation = rotation;
    m_texture = texture;
    m_normalMap = normalMap;
    m_shader = shader;
    m_meshes = meshes;
}

Model::Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Texture* texture, Texture* normalMap, Shader* shader, std::vector<Mesh*> meshes)
{
    m_position = position;
    m_rotation = rotation;
    m_texture = texture;
    m_normalMap = normalMap;
    m_shader = shader;
    m_meshes = meshes;
    m_scale = scale;
}

void Model::Draw(const glm::mat4& viewProjectionMatrix)
{   
    if (!m_visible)
        return;
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
    if (m_texture != nullptr) {
        m_texture->Bind(GL_TEXTURE0);
    }
    if (m_normalMap != nullptr) {
        m_normalMap->Bind(GL_TEXTURE1);
    }
    
    m_shader->SetUniform("u_modelMatrix", modelMatrix);
    m_shader->SetUniform("u_viewProjection", viewProjectionMatrix);
    
    m_shader->SetUniform("u_gSampler", 0);
    m_shader->SetUniform("u_gSamplerNormalMap", 1);
    
    for (Mesh* mesh : m_meshes)
    {
        mesh->Draw();
    }
}

void Model::SetScale(glm::vec3 scale)
{
    m_scale = scale;
    // set the position of the model to the center of the model
    m_position = glm::vec3(m_position.x * m_scale.x, m_position.y * m_scale.y, m_position.z * m_scale.z);
}

void Model::SetPosition(glm::vec3 position)
{
    m_position = position;
}

void Model::SetRotation(glm::vec3 rotation)
{
    m_rotation = rotation;
}

void Model::Rotate(glm::vec3 rotation)
{
    m_rotation += rotation;
}