#ifndef APP_H
#define APP_H

#define GLEW_STATIC
#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>

#include "orthographic_camera.h"
#include "perspective_camera.h"


// abstract class that all apps should inherit from
class App
{
private:
    GLFWwindow *m_window;
    OrthographicCamera *m_orthoCamera;
    PerspectiveCamera *m_perspCamera;

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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
        auto result = glewInit();
        if (result != GLEW_OK)
        {
            fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(result));
            exit(EXIT_FAILURE);
        }

        m_orthoCamera = new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);
        m_perspCamera = new PerspectiveCamera(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
        m_perspCamera->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
        m_perspCamera->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    // runs the app
    void Run();

    // called once before the app runs
    virtual void Init() = 0;

    // on each frame, this is called
    virtual void Update() = 0;

    OrthographicCamera *GetOrthoCamera()
    {
        return m_orthoCamera;
    }

    PerspectiveCamera *GetPerspCamera()
    {
        return m_perspCamera;
    }
};

#endif // APP_H