#include "orthographic_camera.h"
#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_viewMatrix = glm::mat4(1.0f);
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix() 
{
    m_viewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m_viewMatrix = glm::translate(m_viewMatrix, m_position);
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}