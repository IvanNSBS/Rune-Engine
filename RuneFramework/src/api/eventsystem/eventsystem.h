#pragma once

#include <map>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <type_traits>
#include "event.h"
#include "eventcallback.h"

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

        template<typename TEventType>
        void AddCallback(EventCallback<TEventType>* listener)
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);
            
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

        template<typename TEventType>
        void RemoveCallback(EventCallback<TEventType>* listener)
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);

            if(_listeners.count(evtId))
            {
                std::vector<IEventCallback*>* callbacks = &_listeners.at(evtId);
                for(size_t i = callbacks->size() - 1; i >= 0; i--)
                {
                    if(listener->ID() == callbacks->at(i)->ID())
                    {
                        callbacks->erase(callbacks->begin() + i);
                        break;
                    }
                }
            }
        }

        template<typename TEventType>
        void Invoke(TEventType event)
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);

            if(_listeners.count(evtId) && _listeners.at(evtId).size() > 0)
            {
                for(size_t i = 0; i < _listeners[evtId].size(); i++)
                {
                    auto sub = static_cast<EventCallback<TEventType>*>(_listeners.at(evtId).at(i));
                    sub->Invoke(event);
                }
            }
        }

        template<typename TEventType>
        size_t SubCount() 
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);

            if(_listeners.count(evtId))
                return _listeners.at(evtId).size();

            return 0; 
        }

    private:
        std::map<typeOf, std::vector<IEventCallback*>> _listeners;
    };
}