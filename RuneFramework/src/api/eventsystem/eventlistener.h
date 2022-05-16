#pragma once

#include "event.h"
#include <type_traits>

namespace Rune
{
    unsigned int listener_id = 0;

    class IEventListener
    {
    protected:
        unsigned int _id;

    public:
        virtual ~IEventListener() { };
        unsigned int ID() { return _id; }
        friend bool operator==(const IEventListener& l, const IEventListener& r)
        {
            return l._id == r._id;
        }
    };

    template<typename TEvent>
    class EventSubscriber : public IEventListener
    {
    private:
        std::function<void(TEvent&)> _clbk;

    public:
        EventSubscriber(std::function<void(TEvent&)> clbk)
        {
            static_assert(std::is_base_of<IEvent, TEvent>::value, "Template must be of IEvent type");
            _clbk = clbk;
            _id = listener_id + 1;
            listener_id = _id;
        }

        void Invoke(TEvent& evt) { _clbk(evt); }
    };
}