#include "window.h"

class Application 
{
private:
    static inline Window* _window = nullptr;

    Application() { }

    ~Application() {
        delete _window;
    }

    static void CreateOpenGlContext() 
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }

    static void CreateGladContext() 
    {
        // TODO: Make a OpenGL context class to abstract this?
        glfwMakeContextCurrent(_window->GetWindowHandler());
        glfwSetFramebufferSizeCallback(_window->GetWindowHandler(), Window::default_frame_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }
    }

public:
    static void CreateApp(int window_width, int window_height, char* window_name)
    {
        // TODO: Add IFDEF clauses to switch between API and Window Contexts
        CreateOpenGlContext();
        Application::_window = new Window(window_width, window_height, window_name);
        CreateGladContext();
    } 

    inline static void SetWindowFrameBufferCallback(void(*callback_ptr)(GLFWwindow*, int, int)) {
        glfwSetFramebufferSizeCallback(_window->GetWindowHandler(), callback_ptr);
    }

    inline static  Window* GetWindow() { return _window; }

    inline static bool Started() { return _window != nullptr; }

    inline static bool ShouldClose() { return _window->ShouldClose(); }

    inline static void Close() { _window->Close(); }
};