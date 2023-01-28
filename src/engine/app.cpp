#include <engine/app.h>
#include <engine/gl.h>
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <engine/input_manager.h>

static void resize_callback(GLFWwindow *window, int width, int height)
{
//    Set viewport as entire window
   glViewport(0,0, width, height);
  
    App* app = (App*) glfwGetWindowUserPointer(window);
    app->WindowResizeCallback(width, height);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    InputManager::GetInstance().KeyCallback(key, scancode, action, mods);
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    InputManager::GetInstance().CursorPositionCallback(xpos, ypos);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    InputManager::GetInstance().MouseButtonCallback(button, action, mods);
}

// static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
// {
//     InputManager::GetInstance().MouseButtonCallback(button, action, mods);
// }

void App::Run()
{   
    glfwSetWindowUserPointer(m_window, this);
    
    // set resize handler (to handle window resizes)
    glfwSetWindowSizeCallback(m_window, resize_callback);
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    // get version info
    // printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
    // printf("GL_SHADING_LANGUAGE_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    // printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    // printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

    // set the projection matrix
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    while (!glfwWindowShouldClose(m_window))
    {
        glDepthFunc(GL_LESS);
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // sky blue clear color
        // glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
        
        // calculate delta time
        float dt = glfwGetTime();
        glfwSetTime(0.0);
        // call update 
        Update(dt);
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void App::Shutdown()
{   
    glfwSetWindowShouldClose(m_window, true);
    glfwDestroyWindow(m_window);
}

void App::WindowResizeCallback(int width, int height)
{
    m_camera->Resize(width, height);
}

Model* App::CreateCube(Shader* shader)
    {
        glm::vec2 t00(0.0f, 0.0f); // bottom left
        glm::vec2 t01(0.0f, 1.0f); // top left
        glm::vec2 t10(1.0f, 0.0f); // bottom right
        glm::vec2 t11(1.0f, 1.0f); // top right

        auto color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        std::vector<Vertex> vertices = {
            // front face
            Vertex{.position = glm::vec3(-0.5f, -0.5f, 0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = color, .texCoord = t00},
            Vertex{.position = glm::vec3(0.5f, -0.5f, 0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = color, .texCoord = t10},
            Vertex{.position = glm::vec3(-0.5f, 0.5f, 0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = color, .texCoord = t01},
            Vertex{.position = glm::vec3(0.5f, 0.5f, 0.5f), .normal = glm::vec3(0.0f, 0.0f, 1.0f), .color = color, .texCoord = t11},

            // back face
            Vertex{.position = glm::vec3(-0.5f, -0.5f, -0.5f), .normal = glm::vec3(0.0f, 0.0f, -1.0f), .color = color, .texCoord = t00},
            Vertex{.position = glm::vec3(0.5f, -0.5f, -0.5f), .normal = glm::vec3(0.0f, 0.0f, -1.0f), .color = color, .texCoord = t10},
            Vertex{.position = glm::vec3(-0.5f, 0.5f, -0.5f), .normal = glm::vec3(0.0f, 0.0f, -1.0f), .color = color, .texCoord = t01},
            Vertex{.position = glm::vec3(0.5f, 0.5f, -0.5f), .normal = glm::vec3(0.0f, 0.0f, -1.0f), .color = color, .texCoord = t11},

            // left face CCW

            Vertex{.position = glm::vec3(-0.5f, -0.5f, 0.5f), .normal = glm::vec3(-1.0f, 0.0f, 0.0f), .color = color, .texCoord = t00},
            Vertex{.position = glm::vec3(-0.5f, -0.5f, -0.5f), .normal = glm::vec3(-1.0f, 0.0f, 0.0f), .color = color, .texCoord = t10},
            Vertex{.position = glm::vec3(-0.5f, 0.5f, -0.5f), .normal = glm::vec3(-1.0f, 0.0f, 0.0f), .color = color, .texCoord = t11},
            Vertex{.position = glm::vec3(-0.5f, 0.5f, 0.5f), .normal = glm::vec3(-1.0f, 0.0f, 0.0f), .color = color, .texCoord = t01},

            // right face

            Vertex{.position = glm::vec3(0.5f, -0.5f, 0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = color, .texCoord = t00},
            Vertex{.position = glm::vec3(0.5f, -0.5f, -0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = color, .texCoord = t10},
            Vertex{.position = glm::vec3(0.5f, 0.5f, -0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = color, .texCoord = t11},
            Vertex{.position = glm::vec3(0.5f, 0.5f, 0.5f), .normal = glm::vec3(1.0f, 0.0f, 0.0f), .color = color, .texCoord = t01},

            // top face
            Vertex{.position = glm::vec3(-0.5f, 0.5f, 0.5f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = color, .texCoord = t00},
            Vertex{.position = glm::vec3(0.5f, 0.5f, 0.5f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = color, .texCoord = t10},
            Vertex{.position = glm::vec3(0.5f, 0.5f, -0.5f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = color, .texCoord = t11},
            Vertex{.position = glm::vec3(-0.5f, 0.5f, -0.5f), .normal = glm::vec3(0.0f, 1.0f, 0.0f), .color = color, .texCoord = t01},

            // bottom face
            Vertex{.position = glm::vec3(-0.5f, -0.5f, 0.5f), .normal = glm::vec3(0.0f, -1.0f, 0.0f), .color = color, .texCoord = t00},
            Vertex{.position = glm::vec3(0.5f, -0.5f, 0.5f), .normal = glm::vec3(0.0f, -1.0f, 0.0f), .color = color, .texCoord = t10},
            Vertex{.position = glm::vec3(0.5f, -0.5f, -0.5f), .normal = glm::vec3(0.0f, -1.0f, 0.0f), .color = color, .texCoord = t11},
            Vertex{.position = glm::vec3(-0.5f, -0.5f, -0.5f), .normal = glm::vec3(0.0f, -1.0f, 0.0f), .color = color, .texCoord = t01},

        };

        Mesh *mesh = new Mesh(vertices, std::vector<GLuint>{// front
                                                            0, 1, 2, 3, 2, 1,
                                                            // back
                                                            4, 6, 5, 7, 5, 6,
                                                            // left
                                                            8, 10, 9, 11, 10, 8,
                                                            // right
                                                            12, 13, 14, 14, 15, 12,
                                                            // top
                                                            16, 17, 18, 18, 19, 16,
                                                            // bottom
                                                            20, 22, 21, 23, 22, 20

                                        },
                              nullptr);
        std::vector<Mesh *> meshes;
        meshes.push_back(mesh);
        return new Model(
            // pos
            glm::vec3(0.0f),
            // rot
            glm::vec3(0.0f),
            // texture
            (Texture *)nullptr,
            // normal map
            (Texture *)nullptr,
            // shader
            shader,
            // meshes
            meshes);
    }