#include <glad.h>
#include "windowswindow.h"

namespace Rune
{
    void WindowsWindow::Create(uint32_t width, uint32_t height, char* name) 
    {
        _window = glfwCreateWindow(width, height, name, NULL, NULL);
        if (_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
    }

    void WindowsWindow::CreateOpenGlContext() 
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }

    void WindowsWindow::CreateGladContext() 
    {
        glfwMakeContextCurrent(_window);
        glfwSetFramebufferSizeCallback(_window, WindowsWindow::default_frame_callback);
        glfwSwapInterval(_props.vsync);
        
        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }
    }
}