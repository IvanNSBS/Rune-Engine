#include "./window.h"
#include "../../platformdetector.h"

#ifdef RUNE_PLATFORM_WINDOWS
    #include "./windows/windowswindow.h"
#endif

Window* Window::Create(WindowProps props) 
{
    #ifdef RUNE_PLATFORM_WINDOWS
        return new WindowsWindow(props);
    #else
        return nullptr;
    #endif
}