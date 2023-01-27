#include <stdio.h>
#include <engine/gl.h>
#include <memory>
#include <engine/app.h>
#include <engine/shader.h>
#include <engine/input_manager.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

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
    std::vector<Model*> *m_models = new std::vector<Model*>();
    bool m_ortho = false;

    HW2App() : App("HW1: Curtis Covington")
    {
        // create the shader
        m_shader = new Shader("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
        
        Model* model = CreateCube(m_shader);
        model->SetPosition(glm::vec3(1.0f, 1.0f, 0.0f) * 2.0f);
        m_models->push_back(model);

        model = CreateCube(m_shader);
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
        m_shader->SetUniform("dim", glm::vec3(GetCamera()->GetWidth(), GetCamera()->GetHeight(), 1.0f));
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
        if (InputManager::GetInstance().ConsumeKeyDown(Key::Space))
        {
            m_ortho = !m_ortho;
        }

        if (InputManager::GetInstance().IsKeyDown(Key::Up) || InputManager::GetInstance().IsKeyDown(Key::W))
        {

            GetCamera()->Move(Camera::Direction::Up);
        }
        if (InputManager::GetInstance().IsKeyDown(Key::Down) || InputManager::GetInstance().IsKeyDown(Key::S))
        {
            GetCamera()->Move(Camera::Direction::Down);
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
            GetCamera()->Move(Camera::Direction::Forward);
        }
        if (InputManager::GetInstance().IsKeyDown(Key::E))
        {
            GetCamera()->Move(Camera::Direction::Backward);
        }

        // rotate camera
        if (InputManager::GetInstance().IsKeyDown(Key::I))
        {
            GetCamera()->Rotate(Camera::Direction::Up);
        }
        if (InputManager::GetInstance().IsKeyDown(Key::K))
        {
            GetCamera()->Rotate(Camera::Direction::Down);
        }
        if (InputManager::GetInstance().IsKeyDown(Key::J))
        {
            GetCamera()->Rotate(Camera::Direction::Left);
        }
        if (InputManager::GetInstance().IsKeyDown(Key::L))
        {
            GetCamera()->Rotate(Camera::Direction::Right);
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

int main(int argc, char *argv[])
{
    HW2App app;
    app.Run();
    return 0;
}
