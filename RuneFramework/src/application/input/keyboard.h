#pragma once

class Keyboard 
{
public:
    virtual bool IsKeyDown(int keycode) = 0;

    static Keyboard* Create();
};