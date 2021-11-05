#pragma once

#include <glfw/glfw3.h>
#include "../../application/input/keyboard.h"

class WindowsKeyboard : public Keyboard
{
private:
    GLFWwindow* _wnd = nullptr;

public:
    WindowsKeyboard();
    virtual bool IsKeyDown(int keycode) override;
};