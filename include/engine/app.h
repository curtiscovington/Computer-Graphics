#ifndef APP_H
#define APP_H

#include "gl.h"
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <engine/model.h>

#include <engine/camera.h>


// abstract class that all apps should inherit from
class App
{
private:
    GLFWwindow *m_window;
    
    Camera* m_camera;
    bool m_isOrtho = true;

    
public:
    App(const char *title)
    {
        // initialize GLFW  and create a window
        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
            exit(EXIT_FAILURE);
        }
        // glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(640, 480, title, NULL, NULL);
        if (!m_window)
        {
            fprintf(stderr, "ERROR: could not open window with GLFW3\n");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(m_window);
        glViewport(0, 0, 640, 480);

        #ifdef USEGLEW
            // set glew experimental
            glewExperimental = GL_TRUE;
            auto result = glewInit();
            if (result != GLEW_OK)
            {
                fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(result));
                exit(EXIT_FAILURE);
            }
        #endif

        m_camera = new Camera(640, 480, glm::vec3(0.0f, 0.2f, 10.0f));
    }
    // runs the app
    void Run();

    void Shutdown();
    // called once before the app runs
    virtual void Init() = 0;

    // on each frame, this is called
    virtual void Update(float deltaTime) = 0;

    Camera* GetCamera() { return m_camera; }

    void WindowResizeCallback(int width, int height);

    Model* CreateCube(Shader* shader);
};

#endif // APP_H