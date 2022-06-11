#include <stdio.h>
#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <memory>
#include "app.h"
#include "shader.h"
#include "input_manager.h"
#include <glm/glm.hpp>

#include "mesh.h"
Vertex verticies[] = {
    Vertex{ .position = glm::vec3(-0.5f, -0.5f, 0.0f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) },
    Vertex{ .position = glm::vec3(0.5f, -0.5f, 0.0f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) },
    Vertex{ .position = glm::vec3(0.0f, 0.5f, 0.0f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) },
    Vertex{ .position = glm::vec3(0.5f, 0.5f, 0.0f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) },

};



class HW2App : public App
{
public:
    Shader* m_shader;
    Mesh* m_quad;
    HW2App() : App("Homework 2: Curtis Covington") 
    {
        printf("Homework 2: Curtis Covington\n");
        m_shader = new Shader("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
        m_quad = new Mesh(verticies, std::vector<GLuint>{ 2, 1, 0, 3, 2, 0 });
    }
        
    ~HW2App() {}
    
    void Init() {
        
    }

    void Update() {
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            printf("OpenGL error: %s\n", gluErrorString(err));
            exit(0);
        }

        if (InputManager::GetInstance().IsKeyDown(Key::Up)) {
            GetOrthoCamera()->Move(glm::vec3(0.0f, -0.1f, 0.0f));
        }
        if (InputManager::GetInstance().IsKeyDown(Key::Down)) {
            GetOrthoCamera()->Move(glm::vec3(0.0f, 0.1f, 0.0f));
        }
        if (InputManager::GetInstance().IsKeyDown(Key::Left)) {
            GetOrthoCamera()->Move(glm::vec3(0.1f, 0.0f, 0.0f));
        }
        if (InputManager::GetInstance().IsKeyDown(Key::Right)) {
            GetOrthoCamera()->Move(glm::vec3(-0.1f, 0.0f, 0.0f));
        }

        m_quad->Draw(*m_shader, GetOrthoCamera()->GetViewProjectionMatrix());
        

        // m_shader->Unbind();
    }

};

int main(int argc, char *argv[])
{
    printf("Starting");
    HW2App app;
    app.Run();
    return 0;
}

