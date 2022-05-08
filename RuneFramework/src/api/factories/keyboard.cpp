#include "api/input/keyboard.h"
#include "platformdetector.h"

#ifdef RUNE_PLATFORM_WINDOWS
    #include "../../platforms/windows/input/windowskeyboard.h"
#endif

namespace Rune
{
    Keyboard* Keyboard::Create()
    {
        #ifdef RUNE_PLATFORM_WINDOWS
            return new WindowsKeyboard();
        #else
            return nullptr;
        #endif
    }
}