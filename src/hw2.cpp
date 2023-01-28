#include <stdio.h>
#include <engine/gl.h>
#include <memory>
#include <engine/app.h>
#include <engine/shader.h>
#include <engine/input_manager.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/compatibility.hpp>

#include <engine/mesh.h>
#include <engine/camera.h>
#include <engine/texture.h>
#include <engine/model.h>

const float CUBE_VERTICES[] = {
    -1.0f,
    -1.0f,
    1.0f,
    1.0f,
    -1.0f,
    1.0f,
    1.0f,
    -1.0f,
    -1.0f,
    -1.0f,
    -1.0f,
    -1.0f,
    -1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    -1.0f,
    -1.0f,
    1.0f,
    -1.0f,
};

const GLuint CUBE_INDICIES[] = {
    // right face
    6,
    2,
    1,
    1,
    5,
    6,
    // left face
    7,
    4,
    0,
    0,
    3,
    7,
    // top face
    6,
    5,
    4,
    4,
    7,
    6,
    // bottom face
    2,
    3,
    0,
    0,
    1,
    2,
    // back face
    5,
    1,
    0,
    0,
    4,
    5,
    // front face
    6,
    7,
    3,
    3,
    2,
    6,
};

class HW2App : public App
{
public:
    Shader *m_shader;
    Shader *m_lightShader;
    std::vector<Model*> *m_models = new std::vector<Model*>();
    bool m_ortho = false;
    float m_time = 0.0f;

    float m_lastX = 0.0f;
    float m_lastY = 0.0f;
    bool m_firstMouse = true;

    HW2App() : App("HW2: Curtis Covington")
    {
        // create the shader
        m_shader = new Shader("shaders/procedural.vert.glsl", "shaders/procedural.frag.glsl", "shaders/default.geom.glsl");
        m_lightShader = new Shader("shaders/light.vert.glsl", "shaders/light.frag.glsl");

        Model* model = CreateCube(m_shader);
        model->SetPosition(glm::vec3(1.0f, 1.0f, 0.0f) * 2.0f);
        m_models->push_back(model);

        model = CreateCube(m_lightShader);
        model->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        m_models->push_back(model);

        model = CreateCube(m_shader);
        model->SetPosition(glm::vec3(-1.0f, -1.0f, 0.0f) * 2.0f);
        m_models->push_back(model);
    }

    ~HW2App() {}

    void Init()
    {
        GetCamera()->SetSpeed(1.0f);
    }

    void Update(float deltaTime)
    {
        m_time += deltaTime;
        
        // set shader uniforms
        m_shader->SetUniform("dim", glm::vec3(GetCamera()->GetWidth(), GetCamera()->GetHeight(), 1.0f));
        m_shader->SetUniform("u_time", m_time);
        m_shader->SetUniform("u_cameraPos", GetCamera()->GetPosition());

        HandleInput();
        glm::mat4 vpm;
        if (m_ortho)
        {
            vpm = GetCamera()->GetOrthoViewProjectionMatrix();
        }
        else
        {
            vpm = GetCamera()->GetPerspViewProjectionMatrix();
        }

        for (Model* model : *m_models)
        {
            model->Draw(vpm);
        }
        glDepthFunc(GL_LEQUAL);
    }

    void HandleInput()
    {
        if (InputManager::GetInstance().IsMouseButtonDown(MouseButton::Right))
        {
        //     printf("Mouse button down");
            if (m_firstMouse)
            {
                m_lastX = InputManager::GetInstance().GetMouseX();
                m_lastY = InputManager::GetInstance().GetMouseY();
                m_firstMouse = false;
            }
            float offsetX = InputManager::GetInstance().GetMouseX() - m_lastX;
            float offsetY = InputManager::GetInstance().GetMouseY() - m_lastY;

            float sensitivity = 0.001f;
            offsetX *= sensitivity;
            offsetY *= sensitivity;

            float yaw = GetCamera()->GetYaw();
            float pitch = GetCamera()->GetPitch();
            yaw += offsetX;
            pitch -= offsetY;

            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;   

            GetCamera()->SetYaw(yaw);
            GetCamera()->SetPitch(pitch);    
        } else {
            if (!m_firstMouse)
            {
                m_firstMouse = true;
            }
        }

    

        if (InputManager::GetInstance().ConsumeKeyDown(Key::Space))
        {
            m_ortho = !m_ortho;
        }

        if (InputManager::GetInstance().IsKeyDown(Key::Up) || InputManager::GetInstance().IsKeyDown(Key::W))
        {

            GetCamera()->Move(Camera::Direction::Forward);
        }
        if (InputManager::GetInstance().IsKeyDown(Key::Down) || InputManager::GetInstance().IsKeyDown(Key::S))
        {
            GetCamera()->Move(Camera::Direction::Backward);
        }
        if (InputManager::GetInstance().IsKeyDown(Key::Right) || InputManager::GetInstance().IsKeyDown(Key::D))
        {
            GetCamera()->Move(Camera::Direction::Right);
        }
        if (InputManager::GetInstance().IsKeyDown(Key::Left) || InputManager::GetInstance().IsKeyDown(Key::A))
        {
            GetCamera()->Move(Camera::Direction::Left);
        }

        // zoom in and out
        if (InputManager::GetInstance().IsKeyDown(Key::Q))
        {
            GetCamera()->Move(Camera::Direction::Up);
        }
        if (InputManager::GetInstance().IsKeyDown(Key::E))
        {
            GetCamera()->Move(Camera::Direction::Down);
        }

        // if escape is pressed, exit the app
        if (InputManager::GetInstance().ConsumeKeyDown(Key::Escape))
        {
            Shutdown();
        }
    }

    void Shutdown()
    {
        delete m_shader;
        App::Shutdown();
    }
};


