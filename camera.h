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
    
    float m_speed = 0.1f;
    float m_sensitivity = 100.0f;
    float m_zoom = 1.0f;

    
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

    glm::mat4 GetPerspViewProjectionMatrix();
    glm::mat4 GetOrthoViewProjectionMatrix();

    void Move(const glm::vec3& offset);
    void Move(Direction direction);
    void Place(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up);
    void Rotate(const glm::vec3& offset);
    void Rotate(Direction direction);

    void Resize(int width, int height);

    void FirstPerson();
    void Overhead();
    
};

#endif // CAMERA_H