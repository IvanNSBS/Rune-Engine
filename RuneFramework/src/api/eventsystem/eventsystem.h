#pragma once

#include "event.h"
#include <vector>
#include <functional>
#include <map>
#include "windowresizedevent.h"
#include <iostream>

namespace Rune
{
    enum Events
    {
        MouseMoved = 0,
        WindowResized = 1,
        KeyPressed = 2,
        KeyHeld = 3,
        KeyReleased = 4,
    };

    #define EventListener std::function<void(IEvent&)>
    // typedef std::function<void(IEvent*)> EventListener;

    class EventSystem
    {
    public:
        void Subscribe(unsigned int evtId, EventListener listener)
        {
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

        void Unsubscribe(unsigned int evtId, EventListener listener)
        {
            if(_listeners.count(evtId))
            {
                std::vector<EventListener>* listeners = &_listeners.at(evtId);
                // listeners->erase(std::remove(listeners->begin(), listeners->end(), listener), listeners->end());
            }
        }

        void Invoke(IEvent& event)
        {
            if(_listeners.count(event.id()))
            {
                for(EventListener listener : _listeners[event.id()])
                {
                    listener(event);
                }
            }
        }

        int SubCount(unsigned int eventId) 
        {
            if(_listeners.count(eventId))
                return _listeners.at(eventId).size();

            return 0; 
        }

        EventSystem()
        {
            EventListener listener = std::bind(&EventSystem::Test, this, std::placeholders::_1);
            std::cout << "Initial Subcount: " << SubCount(0) << "\n";
            Subscribe(0, listener);
            std::cout << "New Subcount: " << SubCount(0) << "\n";
        }
        ~EventSystem()
        {
            
            std::cout << "Final Subcount: " << SubCount(0);
        }

    private:
        std::map<unsigned int, std::vector<EventListener>> _listeners;

        void Test(IEvent& evt) 
        {
            WindowResizedEvent resize = dynamic_cast<WindowResizedEvent&>(evt);
            std::cout << "Width: " << resize.Width() << ", Height: " << resize.Height() << "\n";
        }
    };
}