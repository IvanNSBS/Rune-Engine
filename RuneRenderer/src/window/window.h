#pragma once

#include <stdint.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
    uint32_t _width, _height;
    char* _title;
    GLFWwindow* _window;

    Window(){ }
    void Create(uint32_t width, uint32_t height, char* name, void(*callback_ptr)(GLFWwindow*, int, int));
    static inline void default_frame_callback(GLFWwindow* wnd, int width, int height) {
        glViewport(0, 0, width, height);
    }

public:
    Window(uint32_t width, uint32_t height, char* name) {
        Create(width, height, name, &Window::default_frame_callback);
    }

    Window(uint32_t width, uint32_t height, char* name, void(*callback_ptr)(GLFWwindow*, int, int)) {
        Create(width, height, name, callback_ptr);
    }

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