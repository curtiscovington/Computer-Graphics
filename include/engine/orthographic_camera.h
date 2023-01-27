// Special thanks to OpenGL youtube series: https://youtu.be/NjKv-HWstxA
#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrthographicCamera
{
    private:
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_viewProjectionMatrix;

        glm::vec3 m_position;
        float m_rotation = 0.0f;

    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return m_position; }
        void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }

        float GetRotation() const { return m_rotation; }
        void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }

        void Move(const glm::vec3& offset) { m_position += offset; RecalculateViewMatrix(); }

        void LookAt(const glm::vec3& target) { m_viewMatrix = glm::lookAt(m_position, target, glm::vec3(0.0f, 1.0f, 0.0f)); RecalculateViewMatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

    private:
        void RecalculateViewMatrix();
};

#endif // ORTHOGRAPHIC_CAMERA_H