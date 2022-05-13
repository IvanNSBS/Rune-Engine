#pragma once

#include "event.h"

namespace Rune
{
    class WindowResizedEvent : public IEvent
    {
    private:
        int _width, _height;
    public:
        WindowResizedEvent(int newWidth, int newHeight)
        {
            _width = newWidth;
            _height = newHeight;
        }
        const int Width() const { return _width; }
        const int Height() const { return _height; }
    };
}