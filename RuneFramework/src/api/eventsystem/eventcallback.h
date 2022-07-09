#pragma once

#include "event.h"
#include <string>
#include <type_traits>

namespace Rune
{

    unsigned int listener_id;
    class IEventCallback
    {
    protected:
        std::string _uid;

    public:
        virtual ~IEventCallback() { };
        const std::string ID() const { return _uid; }
        friend bool operator==(const IEventCallback& l, const IEventCallback& r)
        {
            return l._uid == r._uid;
        }

        friend bool operator==(const IEventCallback& l, const std::string& r)
        {
            return l._uid == r;
        }
    };

    template<typename TEvent>
    class EventCallback : public IEventCallback
    {
    private:
        std::function<void(TEvent&)> _clbk;

    public:
        EventCallback(explicit std::function<void(TEvent&)> clbk)
        {
            static_assert(std::is_base_of<IEvent, TEvent>::value, "Template must be of IEvent type");
            _clbk = clbk;
            _uid = std::to_string(++listener_id);
        }

        EventCallback(explicit std::function<void(TEvent&)> clbk, std::string id)
        {
            static_assert(std::is_base_of<IEvent, TEvent>::value, "Template must be of IEvent type");

            _uid = id;
            _clbk = clbk;
        }

        void Invoke(TEvent& evt) { _clbk(evt); }
    };
}