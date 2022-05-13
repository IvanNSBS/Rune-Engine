#pragma once

#include "event.h"
#include <map>
#include <iostream>
#include <typeinfo>
#include <type_traits>
#include "windowresizedevent.h"

namespace Rune
{
    #define EventListener std::function<void(IEvent&)>
    #define ASSERT_IS_EVENT(TYPE) static_assert(std::is_base_of<IEvent, TYPE>::value, "Template must be of IEvent")
    typedef const std::type_info* typeOf;

    class EventSystem
    {
    public:
        void PollEvents()
        {
            
        }

        template<typename TEventType>
        void Subscribe(EventListener listener)
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);
            
            std::cout << "Subscribing to event <" << evtId->name() << ">\n";

            if(_listeners.count(evtId))
            {
                _listeners.at(evtId).push_back(listener);
            }
            else
            {
                std::vector<EventListener> listeners;
                listeners.push_back(listener);
                _listeners[evtId] = listeners;
            }
        }

        template<typename TEventType>
        void Unsubscribe(EventListener listener)
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);

            if(_listeners.count(evtId))
            {
                std::vector<EventListener>* listeners = &_listeners.at(evtId);
                // listeners->erase(std::remove(listeners->begin(), listeners->end(), listener), listeners->end());
            }
        }

        template<typename TEventType>
        void Invoke(TEventType& event)
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);

            if(_listeners.count(evtId))
            {
                for(EventListener listener : _listeners[evtId])
                {
                    listener(event);
                }
            }
        }

        template<typename TEventType>
        int SubCount() 
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);

            if(_listeners.count(evtId))
            {
                return _listeners.at(evtId).size();
            }

            return 0; 
        }

        EventSystem()
        {
            EventListener listener = std::bind(&EventSystem::Test, this, std::placeholders::_1);
            std::cout << "Initial Subcount: " << SubCount<WindowResizedEvent>() << "\n";
            Subscribe<WindowResizedEvent>(listener);
            std::cout << "New Subcount: " << SubCount<WindowResizedEvent>() << "\n";
        }
        ~EventSystem()
        {
            
            std::cout << "Final Subcount: " << SubCount<WindowResizedEvent>();
        }

    private:
        std::map<typeOf, std::vector<EventListener>> _listeners;

        void Test(IEvent& evt) 
        {
            WindowResizedEvent resize = dynamic_cast<WindowResizedEvent&>(evt);
            std::cout << "Width: " << resize.Width() << ", Height: " << resize.Height() << "\n";
        }
    };
}