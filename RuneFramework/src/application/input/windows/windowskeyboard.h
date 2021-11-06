#pragma once

#include <glfw/glfw3.h>
#include "../keyboard.h"

namespace Rune
{
    class WindowsKeyboard : public Keyboard
    {
    private:
        friend class Keyboard;
        GLFWwindow* _wnd = nullptr;
        WindowsKeyboard();

    public:
        virtual bool IsKeyDown(int keycode) override;
    };
}