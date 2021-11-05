#pragma once

#include <glm/glm.hpp>

class Mouse
{
public:
    virtual float GetMouseX() = 0;
    virtual float GetMouseY() = 0;
    virtual glm::vec2 GetMousePosition() = 0;
    virtual bool IsMouseButtonPressed(int mouseCode) = 0;
};