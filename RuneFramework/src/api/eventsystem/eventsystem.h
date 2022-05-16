#pragma once

#include "event.h"
#include <map>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <type_traits>
#include "windowresizedevent.h"
#include "eventlistener.h"

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
        void Subscribe(EventSubscriber<TEventType>* listener)
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);
            
            if(_listeners.count(evtId))
            {
                _listeners.at(evtId).push_back(static_cast<IEventListener*>(listener));
            }
            else
            {
                std::vector<IEventListener*> listeners;
                listeners.push_back(static_cast<IEventListener*>(listener));
                _listeners[evtId] = listeners;
            }
        }

        template<typename TEventType>
        void Unsubscribe(EventSubscriber<TEventType>* listener)
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);

            if(_listeners.count(evtId))
            {
                std::vector<IEventListener*>* callbacks = &_listeners.at(evtId);
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
        void Invoke(TEventType& event)
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = &typeid(TEventType);

            if(_listeners.count(evtId) && _listeners.at(evtId).size() > 0)
            {
                for(size_t i = 0; i < _listeners[evtId].size(); i++)
                {
                    auto sub = static_cast<EventSubscriber<TEventType>*>(_listeners.at(evtId).at(i));
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

        EventSystem()
        {
            listener = new EventSubscriber<WindowResizedEvent>(
                [](IEvent& x) {
                    // std::cout << "Width: " << x.Width() << ", Height: " << x.Height() << "\n";
                }
            );

            std::cout << "Initial Subcount: " << SubCount<WindowResizedEvent>() << "\n";
            Subscribe(listener);
            std::cout << "New Subcount: " << SubCount<WindowResizedEvent>() << "\n";
        }
        ~EventSystem()
        {
            Unsubscribe(listener);
            std::cout << "Final Subcount: " << SubCount<WindowResizedEvent>();
        }

    private:
        std::map<typeOf, std::vector<IEventListener*>> _listeners;
        EventSubscriber<WindowResizedEvent>* listener;

        void Test(WindowResizedEvent& resize) 
        {
            std::cout << "Width: " << resize.Width() << ", Height: " << resize.Height() << "\n";
        }
    };
}