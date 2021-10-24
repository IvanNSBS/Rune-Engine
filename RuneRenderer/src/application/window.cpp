#include "window.h"

void Window::Create(uint32_t width, uint32_t height, char* name) 
{
    _window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
}