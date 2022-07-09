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
        bool IsSametype(const IEventCallback* clbk) const
		{
			if(!clbk || typeid(*this) != typeid(*clbk))
				return false;

			return true;
		}

    public:
        virtual ~IEventCallback() { };
        virtual bool CompareTo(const IEventCallback* clbk) const = 0;

        friend bool operator==(const IEventCallback& l, const IEventCallback& r)
        {
            // return l.CompareTo(&r);
            return false;
        }
    };

    template<typename TEvent>
    class EventCallback : public IEventCallback
    {
    private:
        void(*_clbk)(TEvent);

    public:
        EventCallback(void(*clbk)(TEvent))
        {
            static_assert(std::is_base_of<IEvent, TEvent>::value, "Template must be of IEvent type");
            _clbk = clbk;
        }
        ~EventCallback() { }

        virtual void Invoke(TEvent& evt) { _clbk(evt); }

        bool CompareTo(const IEventCallback* clbk) const override
        {
            if(!IsSametype(clbk))
                return false;

			const EventCallback<TEvent>* castedEvt = dynamic_cast<const EventCallback<TEvent>*>(clbk);
            return castedEvt->_clbk == this->_clbk;
        }
    };

    template<typename Class, typename TEvent>
    class MemberFuncEventCallback : public EventCallback<TEvent>
    {
    private:
        Class* _instance;
        void(Class::*_member_func)(TEvent);

    public:
        MemberFuncEventCallback(void(Class::*member_func)(TEvent), Class* instance) : EventCallback(nullptr)
        {
            static_assert(std::is_base_of<IEvent, TEvent>::value, "Template must be of IEvent type");
            _instance = instance;
            _member_func = member_func;
        }
        ~MemberFuncEventCallback() { }

        void Invoke(TEvent& evt) override 
        {
            if(_instance)
                (_instance->*_member_func)(evt);
        }

        bool CompareTo(const IEventCallback* clbk) const override
        {
            if(!IsSametype(clbk))
                return false;

			const MemberFuncEventCallback<Class, TEvent>* castedEvt = dynamic_cast<const MemberFuncEventCallback<Class, TEvent>*>(clbk);
            return this->_instance == castedEvt->_instance && castedEvt->_member_func == this->_member_func;
        }
    };
}