#include "./keyboard.h"
#include "../../platformdetector.h"

#ifdef RUNE_PLATFORM_WINDOWS
    #include "./windows/windowskeyboard.h"
#endif

Keyboard* Keyboard::Create()
{
    #ifdef RUNE_PLATFORM_WINDOWS
        return new WindowsKeyboard();
    #else
        return nullptr;
    #endif
}