#pragma once

namespace Rune
{
    class InputManager;

    class InputCommand 
    {
    private:
        int _keycode;

    public:
        inline void const SetKey(int kc) { _keycode = kc; }
        inline int const GetKey() const { return _keycode; }
        virtual void Execute() = 0;

        InputCommand(int keycode): _keycode(keycode) { }
    };
}