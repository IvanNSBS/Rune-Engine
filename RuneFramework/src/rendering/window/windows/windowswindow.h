#pragma once

#include <glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "../window.h"

class WindowsWindow : public Window
{
private:
    GLFWwindow* _window;
    friend class Window;

    static inline void default_frame_callback(GLFWwindow* wnd, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void Create(uint32_t width, uint32_t height, char* name);
    void CreateOpenGlContext();
    void CreateGladContext();
    
    WindowsWindow(WindowProps props) 
    {
        _props = props;
        CreateOpenGlContext();
        Create(_props.width, _props.height, _props.title);
        CreateGladContext();
    }

public:
    ~WindowsWindow() {
        // TODO: Need delete _window?
        glfwSetWindowShouldClose(_window, true);
    }

    virtual void OnUpdate() override {
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    
    virtual inline void Close() override {
        glfwSetWindowShouldClose(_window, true);
    }

    virtual inline bool ShouldClose() override {
        return glfwWindowShouldClose(_window);
    }

    virtual const bool GetVsync() const override {
        return _props.vsync;
    }

    virtual void SetVsync(bool activate) override {
        _props.vsync = activate;
        glfwSwapInterval(activate);
    }

    inline GLFWwindow* GetWindowHandler() const {
        return _window;
    }
};