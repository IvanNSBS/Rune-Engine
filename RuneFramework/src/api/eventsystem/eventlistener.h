#pragma once

#include "event.h"
#include <vector>
#include <functional>

namespace Rune
{
    template<typename TEvent>
    class IEventListener
    {
    private:
        unsigned int _id;
    public:
        IEventListener(unsigned int eventId)
        {
            static_assert(std::is_base_of<IEvent, TEvent>>::value, "Template must be of IEvent type");
        }

        virtual ~IEventListener();
        virtual void Invoke(TEvent& evt) = asd0;
    };
}