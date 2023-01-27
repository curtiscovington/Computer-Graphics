#include <engine/perspective_camera.h>

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far)
{
    m_fov = fov;
    m_aspectRatio = aspectRatio;
    m_near = near;
    m_far = far;
}

void PerspectiveCamera::RecalculateViewMatrix()
{
    m_viewMatrix = glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    m_viewMatrix = glm::translate(m_viewMatrix, -m_position);
}

