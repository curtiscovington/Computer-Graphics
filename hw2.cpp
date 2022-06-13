#include <stdio.h>
#include "gl.h"
#include <memory>
#include "app.h"
#include "shader.h"
#include "input_manager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mesh.h"
#include "camera.h"
#include "texture.h"
#include "model.h"



class HW2App : public App
{
public:
    Shader* m_shader;
    Shader* m_leavesShader;
    Mesh* m_quad;
    std::vector<Model*> m_models;

    bool m_ortho = false;
    bool m_firstPerson = true;
    float m_totalTime = 0.0f;

    HW2App() : App("Homework 2: Curtis Covington") 
    {
        printf("Homework 2: Curtis Covington\n");
        glm::vec2 t00(0.0f, 0.0f); // bottom left
        glm::vec2 t01(0.0f, 1.0f); // top left
        glm::vec2 t10(1.0f, 0.0f); // bottom right
        glm::vec2 t11(1.0f, 1.0f); // top right

        auto brown = glm::vec4(0.5f, 0.35f, 0.05f, 1.0f);
        std::vector<Vertex> vertices = {
            // front face
            Vertex{ .position = glm::vec3(-0.5f, -0.5f, 0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = brown, .texCoord = t00 },
            Vertex{ .position = glm::vec3(0.5f, -0.5f, 0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = brown, .texCoord = t10 },
            Vertex{ .position = glm::vec3(0.5f, 0.5f, 0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = brown, .texCoord = t11 },
            Vertex{ .position = glm::vec3(-0.5f, 0.5f, 0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = brown, .texCoord = t01 },
            
            // back face
            Vertex{ .position = glm::vec3(-0.5f, -0.5f, -0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = brown, .texCoord = t00 },
            Vertex{ .position = glm::vec3(0.5f, -0.5f, -0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = brown, .texCoord = t10 },
            Vertex{ .position = glm::vec3(0.5f, 0.5f, -0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = brown, .texCoord = t11 },
            Vertex{ .position = glm::vec3(-0.5f, 0.5f, -0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = brown, .texCoord = t01 },

            // left face
            Vertex{ .position = glm::vec3(-0.5f, -0.5f, 0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = brown, .texCoord = t00 },
            Vertex{ .position = glm::vec3(-0.5f, -0.5f, -0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = brown, .texCoord = t10 },
            Vertex{ .position = glm::vec3(-0.5f, 0.5f, -0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = brown, .texCoord = t11 },
            Vertex{ .position = glm::vec3(-0.5f, 0.5f, 0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = brown, .texCoord = t01 },

            // right face

            Vertex{ .position = glm::vec3(0.5f, -0.5f, 0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = brown, .texCoord = t00 },
            Vertex{ .position = glm::vec3(0.5f, -0.5f, -0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = brown, .texCoord = t10 },
            Vertex{ .position = glm::vec3(0.5f, 0.5f, -0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = brown, .texCoord = t11 },
            Vertex{ .position = glm::vec3(0.5f, 0.5f, 0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = brown, .texCoord = t01 },

            // top face
            Vertex{ .position = glm::vec3(-0.5f, 0.5f, 0.5f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = brown, .texCoord = t00 },
            Vertex{ .position = glm::vec3(0.5f, 0.5f, 0.5f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = brown, .texCoord = t10 },
            Vertex{ .position = glm::vec3(0.5f, 0.5f, -0.5f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = brown, .texCoord = t11 },
            Vertex{ .position = glm::vec3(-0.5f, 0.5f, -0.5f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = brown, .texCoord = t01 },

            // bottom face
            Vertex{ .position = glm::vec3(-0.5f, -0.5f, 0.5f), .normal = glm::vec3(0.0f, -1.0f, 0.0f), .color = brown, .texCoord = t00 },
            Vertex{ .position = glm::vec3(0.5f, -0.5f, 0.5f), .normal = glm::vec3(0.0f, -1.0f, 0.0f), .color = brown, .texCoord = t10 },
            Vertex{ .position = glm::vec3(0.5f, -0.5f, -0.5f), .normal = glm::vec3(0.0f, -1.0f, 0.0f), .color = brown, .texCoord = t11 },
            Vertex{ .position = glm::vec3(-0.5f, -0.5f, -0.5f), .normal = glm::vec3(0.0f, -1.0f, 0.0f), .color = brown, .texCoord = t01 },

        };

        Texture* woodTexture = new Texture(GL_TEXTURE_2D, "assets/wood.jpg");
        Texture* leavesTexture = new Texture(GL_TEXTURE_2D, "assets/leaves.jpg");
        Texture* grassTexture = new Texture(GL_TEXTURE_2D, "assets/grass.jpg");
        woodTexture->Load();
        leavesTexture->Load();
        grassTexture->Load(GL_REPEAT, GL_REPEAT);
        m_shader = new Shader("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
        m_leavesShader = new Shader("shaders/leaves.vert.glsl", "shaders/shader.frag.glsl");

        // ground
        Mesh* quad = new Mesh(std::vector<Vertex>{
            Vertex{ .position = glm::vec3(-1.0f, -1.0f, -1.0f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), .texCoord = t00 * 64.0f },
            Vertex{ .position = glm::vec3(1.0f, -1.0f, -1.0f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), .texCoord = t01 * 64.0f },
            Vertex{ .position = glm::vec3(1.0f, -1.0f, 1.0f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), .texCoord = t10 * 64.0f },
            Vertex{ .position = glm::vec3(-1.0f, -1.0f, 1.0f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), .texCoord = t11 * 64.0f },
        },std::vector<GLuint>{
            0, 1, 2,
            2, 3, 0
        }, grassTexture);
        
        // cube
        m_quad = new Mesh(vertices, std::vector<GLuint>{ 
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            4, 5, 6,
            6, 7, 4,
            // back
            8, 9, 10,
            10, 11, 8,
            // left
            12, 13, 14,
            14, 15, 12,
            // top
            16, 17, 18,
            18, 19, 16,
            // bottom
            20, 21, 22,
            22, 23, 20
            
         }, woodTexture);

        std::vector<glm::vec3> treePositions;
        std::vector<glm::vec3> treeRotations;

        // generate 10 random positions for the trees
        for (int i = 0; i < 100; i++)
        {
            glm::vec3 position;
            glm::vec3 rotation;
            // random x, z between -100 and 100
            position.x = (float)(rand() % 200) - 100.0f;
            position.y = 0.0f;
            position.z = (float)(rand() % 200) - 100.0f;
            treePositions.push_back(position);

            // random rotation between 0 and 360
            rotation.y = (float)(rand() % 360);

            treeRotations.push_back(rotation);
        }

        treePositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        treeRotations.push_back(glm::vec3(0.0f, 45.0f, 0.0f));
        for (int i = 0; i < treePositions.size(); i++)
        {
            glm::vec3 position = treePositions[i];
            glm::vec3 rotation = treeRotations[i];
            m_models.push_back(new Model(position + glm::vec3(0.0f, 0.5f, 0.0f), rotation, woodTexture, m_shader, std::vector<Mesh*>{ m_quad }));
            m_models.push_back(new Model(position + glm::vec3(0.0f, -0.5f, 0.0f),rotation, woodTexture, m_shader, std::vector<Mesh*>{ m_quad }));
            m_models.push_back(new Model(position + glm::vec3(0.0f, 1.5f, 0.0f), rotation, leavesTexture, m_leavesShader, std::vector<Mesh*>{ m_quad }));
            m_models.push_back(new Model(position + glm::vec3(1.0f, 1.5f, 0.0f), rotation, leavesTexture, m_leavesShader, std::vector<Mesh*>{ m_quad }));
            m_models.push_back(new Model(position + glm::vec3(0.0f, 1.5f, 1.0f), rotation, leavesTexture, m_leavesShader, std::vector<Mesh*>{ m_quad }));
            m_models.push_back(new Model(position + glm::vec3(-1.0f, 1.5f, 0.0f), rotation, leavesTexture, m_leavesShader, std::vector<Mesh*>{ m_quad }));
            m_models.push_back(new Model(position + glm::vec3(0.0f, 1.5f, -1.0f), rotation, leavesTexture, m_leavesShader, std::vector<Mesh*>{ m_quad }));
            m_models.push_back(new Model(position + glm::vec3(0.0f, 2.5f, 0.0f), rotation, leavesTexture, m_leavesShader, std::vector<Mesh*>{ m_quad }));
        }
        

        m_models.push_back(new Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(200.0f, 1.0f, 200.0f), grassTexture, m_shader, std::vector<Mesh*>{ quad }));
    }
        
    ~HW2App() {}
    
    void Init() {
        
    }

    void Update(float deltaTime) {
        m_totalTime += deltaTime;
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            printf("OpenGL error: %s\n", gluErrorString(err));
            exit(0);
        }
        
        if (InputManager::GetInstance().IsKeyDown(Key::Up)) {
            if (m_firstPerson) {
                GetCamera()->Move(Camera::Direction::Forward);
            } else {
                GetCamera()->Move(Camera::Direction::Up);
            }
        }
        if (InputManager::GetInstance().IsKeyDown(Key::Down)) {
            if (m_firstPerson) {
                GetCamera()->Move(Camera::Direction::Backward);
            } else {
                GetCamera()->Move(Camera::Direction::Down);
            }
        }
        if (InputManager::GetInstance().IsKeyDown(Key::Right)) {
            if (m_firstPerson) {
                GetCamera()->Rotate(Camera::Direction::Left);
            } else {
                GetCamera()->Move(Camera::Direction::Right);
            }
        }
        if (InputManager::GetInstance().IsKeyDown(Key::Left)) {
            if (m_firstPerson) {
                GetCamera()->Rotate(Camera::Direction::Right);
            } else {
                GetCamera()->Move(Camera::Direction::Left);
            }
        }

        if (InputManager::GetInstance().IsKeyDown(Key::M)) {
            GetCamera()->Move(glm::vec3(0.0f, 0.0f, -0.1f));
        }
        if (InputManager::GetInstance().IsKeyDown(Key::N)) {
            GetCamera()->Move(glm::vec3(0.0f, 0.0f, 0.1f));
        }

        // set first person
        if (InputManager::GetInstance().ConsumeKeyDown(Key::F)) {
            m_firstPerson = !m_firstPerson;
            if (m_firstPerson) {
                m_ortho = false;
                GetCamera()->FirstPerson();
            } else {
                m_ortho = true;
                GetCamera()->Overhead();
            }
        } 

        m_leavesShader->Bind();
        m_leavesShader->SetUniform("u_time", m_totalTime);

        if (InputManager::GetInstance().ConsumeKeyDown(Key::O)) {
            m_ortho = true;
        }

        if (InputManager::GetInstance().ConsumeKeyDown(Key::P)) {
            m_ortho = false;
        }
        
        // m_quad->Draw(*m_shader, GetOrthoCamera()->GetViewProjectionMatrix());
        if (m_ortho) {
            for (Model* model : m_models) {
                model->Draw(GetCamera()->GetOrthoViewProjectionMatrix());
            }
        } else {
            for (Model* model : m_models) {
                model->Draw(GetCamera()->GetPerspViewProjectionMatrix());
            }
        }
        
        

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

