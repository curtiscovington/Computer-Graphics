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

class HW3App : public App
{
public:
    int m_currentShader = 0;
    std::vector<Shader*> m_shaders = std::vector<Shader*>();
    std::vector<Model*> m_models = std::vector<Model*>();
    bool m_ortho = true;
    float m_time = 0.0f;

    float m_lastX = 0.0f;
    float m_lastY = 0.0f;
    bool m_firstMouse = true;

    HW3App() : App("HW3: Curtis Covington")
    {
        // create the shader
        m_shaders.push_back(new Shader("shaders/fullscreen.vert.glsl", "shaders/fullscreen.frag.glsl"));
        m_shaders.push_back(new Shader("shaders/procedural.vert.glsl", "shaders/dot.frag.glsl", "shaders/default.geom.glsl"));

        glm::vec2 t00(0.0f, 0.0f); // bottom left
        glm::vec2 t01(0.0f, 1.0f); // top left
        glm::vec2 t10(1.0f, 0.0f); // bottom right
        glm::vec2 t11(1.0f, 1.0f); // top right

        glm::vec4 color(1.0f);
        // create a quad to render the screen in
        std::vector<Vertex> vertices = {
            Vertex{.position = glm::vec3(-1.0f, -1.0f, 0.0f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = color, .texCoord = t00},
            Vertex{.position = glm::vec3(1.0f, -1.0f, 0.0f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = color, .texCoord = t10},
            Vertex{.position = glm::vec3(-1.0f, 1.0f, 0.0f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = color, .texCoord = t01},
            Vertex{.position = glm::vec3(1.0f, 1.0f, 0.0f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = color, .texCoord = t11},
        };

        std::vector<unsigned int> indices = { 0, 1, 2, 3, 2, 1 };
        
        Mesh* mesh = new Mesh(vertices, indices, nullptr);

        std::vector<Mesh*> meshes = std::vector<Mesh*>();
        meshes.push_back(mesh);

        // create the model
        m_models.push_back(new Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), nullptr, nullptr, m_shaders[0], meshes));
    }

    ~HW3App() {}

    void Init()
    {
        GetCamera()->SetSpeed(1.0f);
    }

    void Update(float deltaTime)
    {
        // calculate fps using delta time
        static float fps = 0.0f;
        static float fpsTimer = 0.0f;
        fpsTimer += deltaTime;
        if (fpsTimer > 0.25f)
        {
            fps = 1.0f / deltaTime;
            fpsTimer = 0.0f;
        }

        // update the window title
        char title[256];
        sprintf(title, "HW3: Curtis Covington - FPS: %.2f", fps);
        SetWindowTitle(title);

        m_time += deltaTime;
        
        // set shader uniforms
        for (Shader* shader : m_shaders)
        {
            shader->SetUniform("u_time", m_time);
            shader->SetUniform("u_cameraPos", GetCamera()->GetPosition());
            shader->SetUniform("dim", glm::vec3(GetCamera()->GetWidth(), GetCamera()->GetHeight(), 1.0f));
        }

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

        for (Model* model : m_models)
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

    
        if (InputManager::GetInstance().ConsumeKeyDown(Key::Tab))
        {
            m_currentShader++;
            m_currentShader = m_currentShader % m_shaders.size();
            m_models[0]->SetShader(m_shaders[m_currentShader]);
            m_models[2]->SetShader(m_shaders[m_currentShader]);
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
        for (Shader* shader : m_shaders)
        {
            delete shader;
        }
        App::Shutdown();
    }
};


