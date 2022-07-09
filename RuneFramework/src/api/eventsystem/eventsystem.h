#pragma once

#include <map>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <type_traits>
#include <memory>
#include "event.h"
#include "eventcallback.h"
#include "windowresizedevent.h"

#define TYPEOF(x) &typeid(x)

namespace Rune
{
    #define ASSERT_IS_EVENT(TYPE) static_assert(std::is_base_of<IEvent, TYPE>::value, "Template must be of IEvent")
    typedef const std::type_info* typeOf;

    class EventSystem
    {
    public:
        void PollEvents()
        {

        }

        ~EventSystem()
        {
            for(auto it = _listeners.begin(); it != _listeners.end(); it++)
            {
                for(size_t i = it->second.size(); i-- > 0;)
                {
                    delete it->second.at(i);
                    it->second.pop_back();
                }
            }
        }

        template<typename TEvt, class Class>
        void Bind(void(Class::*member_func)(TEvt), Class* instance)
        {
            EventCallback<TEvt>* evt = new MemberFuncEventCallback<Class, TEvt>(member_func, instance);
            AddCallback(evt);
        }

        template<typename TEvt>
        void Bind(void(*foo)(TEvt))
        {
            EventCallback<TEvt>* clbk = new EventCallback<TEvt>(foo);
            AddCallback(clbk);
        }

        template<typename TEvt, typename Class>
        bool Unbind(void(Class::*member_func)(TEvt), Class* instance)
        {
            std::unique_ptr<EventCallback<TEvt>> clbk = std::make_unique<MemberFuncEventCallback<Class, TEvt>>(member_func, instance);
            return RemoveCallback<TEvt>(clbk.get()); 
        }

        template<typename TEvt>
        bool Unbind(void(*foo)(TEvt))
        {
            std::unique_ptr<EventCallback<TEvt>> clbk = std::make_unique<EventCallback<TEvt>>(foo);
            return RemoveCallback<TEvt>(clbk.get()); 
        }

        template<typename TEvt>
        void Invoke(TEvt event)
        {
            ASSERT_IS_EVENT(TEvt);
            typeOf evtId = TYPEOF(TEvt);

            if(_listeners.count(evtId) && _listeners.at(evtId).size() > 0)
            {
                for(size_t i = 0; i < _listeners[evtId].size(); i++)
                {
                    auto sub = static_cast<EventCallback<TEvt>*>(_listeners.at(evtId).at(i));
                    sub->Invoke(event);
                }
            }
        }

    private:
        std::map<typeOf, std::vector<IEventCallback*>> _listeners;

        template<typename TEvt>
        size_t SubCount() 
        {
            ASSERT_IS_EVENT(TEvt);
            typeOf evtId = TYPEOF(TEvt);

            if(_listeners.count(evtId))
                return _listeners.at(evtId).size();

            return 0; 
        }

        template<typename TEvt>
        void AddCallback(EventCallback<TEvt>* listener)
        {
            ASSERT_IS_EVENT(TEvt);
            typeOf evtId = TYPEOF(TEvt);
            
            if(_listeners.count(evtId))
            {
                _listeners.at(evtId).push_back(static_cast<IEventCallback*>(listener));
            }
            else
            {
                std::vector<IEventCallback*> listeners;
                listeners.push_back(static_cast<IEventCallback*>(listener));
                _listeners[evtId] = listeners;
            }
        }

        template<typename TEvt>
        bool RemoveCallback(EventCallback<TEvt>* listener)
        {
            ASSERT_IS_EVENT(TEvt);
            typeOf evtId = TYPEOF(TEvt);

            bool result = false;
            if(_listeners.count(evtId))
            {
                std::vector<IEventCallback*>* callbacks = &_listeners.at(evtId);
                for(size_t i = callbacks->size() - 1; i >= 0; i--)
                {
                    if(listener->CompareTo(callbacks->at(i)))
                    {
                        IEventCallback* toRemove = callbacks->at(i);
                        callbacks->erase(callbacks->begin() + i);
                        result = true;
                        delete toRemove;
                        break;
                    }
                }
            }

            return result;
        }
    };
}