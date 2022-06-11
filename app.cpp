#include "app.h"
#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "input_manager.h"

static void debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

static void resize_callback(GLFWwindow *window, int width, int height)
{
  //  Set viewport as entire window
//    glViewport(0,0, width, height);
//    //  Select projection matrix
//    glMatrixMode(GL_PROJECTION);
//    //  Set projection to identity
//    glLoadIdentity();
//    //  Orthogonal projection:  unit cube adjusted for aspect ratio
//    double asp = (height>0) ? (double)width/height : 1;
//    glOrtho(-asp,+asp, -1.0,+1.0, -1.0,+1.0);
//    //  Select model view matrix
//    glMatrixMode(GL_MODELVIEW);
//    //  Set model view to identity
//    glLoadIdentity();
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    InputManager::GetInstance().KeyCallback(key, scancode, action, mods);
}


void App::Run()
{   
    // debug callback    
    glDebugMessageCallback(debug_callback, nullptr);
    // set resize handler (to handle window resizes)
    glfwSetWindowSizeCallback(m_window, resize_callback);
    glfwSetKeyCallback(m_window, key_callback);

    // get version info
    printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
    printf("GL_SHADING_LANGUAGE_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

    glEnable(GL_DEBUG_OUTPUT);
    // set the projection matrix
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    while (!glfwWindowShouldClose(m_window))
    {
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // set the projection matrix
       
        // call update 
        Update();
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

}