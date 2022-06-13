#include "app.h"
#include "gl.h"
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "input_manager.h"

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

    // get version info
    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
    printf("GL_SHADING_LANGUAGE_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

    // set the projection matrix
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    while (!glfwWindowShouldClose(m_window))
    {
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // sky blue clear color
        glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
        // calculate delta time
        float dt = glfwGetTime();
        glfwSetTime(0.0);
        // call update 
        Update(dt);
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

}

void App::WindowResizeCallback(int width, int height)
{
    m_camera->Resize(width, height);
}