#pragma once

#include "event.h"
#include <type_traits>

namespace Rune
{
    unsigned int listener_id = 0;

    class IEventCallback
    {
    protected:
        unsigned int _id;

    public:
        virtual ~IEventCallback() { };
        unsigned int ID() { return _id; }
        friend bool operator==(const IEventCallback& l, const IEventCallback& r)
        {
            return l._id == r._id;
        }
    };

    template<typename TEvent>
    class EventCallback : public IEventCallback
    {
    private:
        std::function<void(TEvent&)> _clbk;

    public:
        EventCallback(std::function<void(TEvent&)> clbk)
        {
            static_assert(std::is_base_of<IEvent, TEvent>::value, "Template must be of IEvent type");
            _clbk = clbk;
            _id = listener_id + 1;
            listener_id = _id;
        }

        void Invoke(TEvent& evt) { _clbk(evt); }
    };
}