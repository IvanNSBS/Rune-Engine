#include "../rendering/window/window.h"
#include "../../platformdetector.h"

#ifdef RUNE_PLATFORM_WINDOWS
    #include "../../platforms/windows/window/windowswindow.h"
#endif

namespace Rune 
{
    Window* Window::Create(WindowProps props) 
    {
        #ifdef RUNE_PLATFORM_WINDOWS
            return new WindowsWindow(props);
        #else
            return nullptr;
        #endif
    }
}