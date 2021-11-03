#pragma once

class InputManager;

class InputCommand 
{
private:
    friend class InputManager;
    int _keycode;
    inline void const SetKey(int kc) { _keycode = kc; }

public:
    inline int const GetKey() const { return _keycode; }
    virtual void Execute() = 0;

    InputCommand(int keycode): _keycode(keycode) { }
};