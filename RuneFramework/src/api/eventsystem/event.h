#pragma once

#include <vector>
#include <functional>

namespace Rune
{
    class IEvent
    {
    public:
        virtual unsigned int id() = 0;
        virtual ~IEvent() { }
    };
}