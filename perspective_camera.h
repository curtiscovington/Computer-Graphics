#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

class PerspectiveCamera
{
private:
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_viewProjectionMatrix;

    glm::vec3 m_position;
    float m_rotation = 0.0f;

    float m_fov = 45.0f;
    float m_aspectRatio = 1.0f;
    float m_near = 0.1f;
    float m_far = 100.0f;

    void RecalculateViewMatrix();

    void RecalculateProjectionMatrix();

    void RecalculateViewProjectionMatrix();

    public:
        PerspectiveCamera(float fov, float aspectRatio, float near, float far);

        const glm::vec3& GetPosition() const { return m_position; }
        void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }

        float GetRotation() const { return m_rotation; }
        void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

        void Move(const glm::vec3& offset) { m_position += offset; RecalculateViewMatrix(); }
        void LookAt(const glm::vec3& target) { m_viewMatrix = glm::lookAt(m_position, target, glm::vec3(0.0f, 1.0f, 0.0f)); RecalculateViewMatrix(); }

        float GetFov() const { return m_fov; }

        float GetAspectRatio() const { return m_aspectRatio; }

        float GetNear() const { return m_near; }

        float GetFar() const { return m_far; }

        void SetFov(float fov) { m_fov = fov; RecalculateProjectionMatrix(); RecalculateViewProjectionMatrix(); }

        void SetAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; RecalculateProjectionMatrix(); RecalculateViewProjectionMatrix(); }

        void SetNear(float near) { m_near = near; RecalculateProjectionMatrix(); RecalculateViewProjectionMatrix(); }

        void SetFar(float far) { m_far = far; RecalculateProjectionMatrix(); RecalculateViewProjectionMatrix(); }

        void SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_projectionMatrix = projectionMatrix; RecalculateViewProjectionMatrix(); }

        void SetViewMatrix(const glm::mat4& viewMatrix) { m_viewMatrix = viewMatrix; RecalculateViewProjectionMatrix(); }

        void SetViewProjectionMatrix(const glm::mat4& viewProjectionMatrix) { m_viewProjectionMatrix = viewProjectionMatrix; }
};


#endif // PERSPECTIVE_CAMERA_H