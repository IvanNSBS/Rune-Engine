#pragma once

#include <stdint.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Application;

class Window
{
private:
    uint32_t _width, _height;
    char* _title;
    GLFWwindow* _window;
    friend class Application;

    Window(){ }
    Window(uint32_t width, uint32_t height, char* name) {
        Create(width, height, name);
    }

    void Create(uint32_t width, uint32_t height, char* name);
    
    static inline void default_frame_callback(GLFWwindow* wnd, int width, int height) {
        glViewport(0, 0, width, height);
    }

public:

    ~Window(){
        glfwSetWindowShouldClose(_window, true);
    }

    inline bool ShouldClose() {
        return glfwWindowShouldClose(_window);
    }

    inline void Close() {
        glfwSetWindowShouldClose(_window, true);
    }

    inline GLFWwindow* GetWindowHandler() const {
        return _window;
    }
};