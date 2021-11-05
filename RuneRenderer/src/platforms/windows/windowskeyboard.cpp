#include "windowswindow.h"
#include "windowskeyboard.h"
#include "../../application/application.h"

WindowsKeyboard::WindowsKeyboard() 
{
    Window* window = Application::GetWindow();
    WindowsWindow* windowsWindow = static_cast<WindowsWindow*>(window);
    _wnd = windowsWindow->GetWindowHandler();
}

bool WindowsKeyboard::IsKeyDown(int keycode) 
{
    return glfwGetKey(_wnd, keycode) == GLFW_PRESS;
}