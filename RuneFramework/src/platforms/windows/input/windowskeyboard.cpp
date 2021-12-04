#include "../window/windowswindow.h"
#include "../../../api/input/keyboard.h"
#include "../../../api/application.h"
#include "./windowskeyboard.h"

namespace Rune
{
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
}