#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

class Camera {
private:
    
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;

    int m_width;
    int m_height;

    float m_fov = 45.0f;
    
    float m_speed = 0.1f;
    float m_sensitivity = 100.0f;
    float m_zoom = 1.0f;
    bool m_viewEntireWorld = false;

    
public:
    enum Direction {
        Forward,
        Backward,
        Left,
        Right,
        Up,
        Down
    };
    Camera(int width, int height, glm::vec3 position);

    void SetSpeed(float speed) { m_speed = speed; }
    glm::vec3 GetPosition() const { return m_position; }
    glm::vec3 GetForward() const { return m_forward; }
    glm::vec3 GetUp() const { return m_up; }
    float GetFOV() const { return m_fov; }
    float GetAspectRatio() const { return (float)m_width / (float)m_height; }
    float GetWidth() const { return m_width; }
    float GetHeight() const { return m_height; }
    glm::mat4 GetPerspViewProjectionMatrix();
    glm::mat4 GetOrthoViewProjectionMatrix();

    void Move(const glm::vec3& offset);
    void Move(Direction direction);
    void Place(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up);
    void Rotate(const glm::vec3& offset);
    void Rotate(Direction direction);
    void Orbit(const glm::vec3& point, const glm::vec3& offset);

    void Resize(int width, int height);

    void FirstPerson();
    void Overhead();
    void World();
    
};

#endif // CAMERA_H