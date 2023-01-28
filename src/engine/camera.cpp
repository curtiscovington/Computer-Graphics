#include <engine/camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
Camera::Camera(int width, int height, glm::vec3 position)
{
    m_position = position;
    m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_width = width;
    m_height = height;
}

glm::mat4 Camera::GetPerspViewProjectionMatrix()
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    
    // calculate view based on pitch and yaw
    m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_forward.y = sin(glm::radians(m_pitch));
    m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_forward = glm::normalize(m_forward);

    // printf("m_forward: %f, %f, %f, %f, %f\n", m_forward.x, m_forward.y, m_forward.z, m_yaw, m_pitch);
    
    view = glm::lookAt(m_position, m_position + m_forward, m_up);
    projection = glm::perspective(glm::radians(m_fov), (float)m_width / (float)m_height, 1.0f, 400.0f);
    
    return projection * view;
    // return glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f) * glm::lookAt(m_position, m_position + m_forward, m_up);
}

glm::mat4 Camera::GetOrthoViewProjectionMatrix()
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // zoom
    float zoom = 10.0f;
    // maintain aspect ratio
    float aspectRatio = (float)m_width / (float)m_height;
    float left = -aspectRatio * zoom;
    float right = aspectRatio * zoom;
    float bottom = -1.0f * zoom;
    float top = 1.0f * zoom;

    // calculate view based on pitch and yaw
    m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_forward.y = sin(glm::radians(m_pitch));
    m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_forward = glm::normalize(m_forward);

    view = glm::lookAt(m_position, m_position + m_forward, m_up);
    projection = glm::ortho(left, right, bottom, top, 0.1f, 100.0f);
    return projection * view;
    // return glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height, 0.1f, 100.0f) * glm::lookAt(m_position, m_position + m_forward, m_up);
}

void Camera::Resize(int width, int height)
{
    m_width = width;
    m_height = height;
}

void Camera::Rotate(const glm::vec3& offset)
{
    glm::vec3 right = glm::cross(m_forward, m_up);
    glm::vec3 up = glm::cross(right, m_forward);
    m_forward = glm::normalize(m_forward + offset.x * right + offset.y * up);
    m_up = glm::normalize(m_up + offset.x * up + offset.y * right);
    
}

void Camera::Rotate(Direction direction)
{
    glm::vec3 right = glm::cross(m_forward, m_up);
    glm::vec3 up = glm::cross(right, m_forward);
    switch (direction)
    {
    case Forward:
        m_forward = glm::normalize(m_forward + m_speed * m_forward);
        break;
    case Backward:
        m_forward = glm::normalize(m_forward - m_speed * m_forward);
        break;
    case Left:
        m_forward = glm::normalize(m_forward + m_speed * right);
        break;
    case Right:
        m_forward = glm::normalize(m_forward - m_speed * right);
        break;
    case Up:
        m_forward = glm::normalize(m_forward + m_speed * up);
        break;
    case Down:
        m_forward = glm::normalize(m_forward - m_speed * up);
        break;
    }
}

void Camera::Orbit(const glm::vec3& point, const glm::vec3& offset)
{
    // float radius = glm::distance(m_position, point);
    
    // // a sphere with radius cenered at the point
    // // move position by offset and get the nearest point on the sphere
    // glm::vec3 newPosition = m_position + offset;
    // // get the nearest point on the sphere
    // glm::vec3 nearestPoint = glm::normalize(newPosition - point) * radius + point;
    // // move the camera to the nearest point
    // m_position = nearestPoint;
    // // get the new forward vector
    // m_forward = glm::normalize(newPosition - m_position);
    // // get the new up vector
    
}

void Camera::Move(const glm::vec3& offset)
{
    // move the position in the direction of the forward vector by the offset
    m_position += m_forward * offset;
    // m_position += offset;
}

void Camera::Move(Direction direction)
{
    glm::vec3 right = glm::cross(m_forward, m_up);
    glm::vec3 up = glm::cross(right, m_forward);
    switch (direction)
    {
    case Forward:
        m_position += m_forward * m_speed;
        break;
    case Backward:
        m_position -= m_forward * m_speed;
        break;
    case Left:
        m_position -= right * m_speed;
        break;
    case Right:
        m_position += right * m_speed;
        break;
    case Up:
        m_position += up * m_speed;
        break;
    case Down:
        m_position -= up * m_speed;
        break;
    }
}

void Camera::Place(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up)
{
    m_position = position;
    m_forward = forward;
    m_up = up;
}

void Camera::Overhead()
{
    m_forward = glm::vec3(0.0f, -1.0f, 0.0f);
    m_up = glm::vec3(0.0f, 0.0f, -1.0f);
    m_position = glm::vec3(0.0f, 20.0f, 0.0f);
}

void Camera::FirstPerson()
{
    m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_position = glm::vec3(0.0f, 0.0f, 10.0f);
}

void Camera::World()
{
    m_forward = glm::vec3(0.0f, -1.0f, 0.0f);
    m_up = glm::vec3(0.0f, 0.0f, -1.0f);
    m_position = glm::vec3(0.0f, 200.0f, 0.0f);
    m_viewEntireWorld = true;
}