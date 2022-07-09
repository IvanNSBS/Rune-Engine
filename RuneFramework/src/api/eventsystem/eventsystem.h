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

#define TEST_STR(thing) std::string(#thing)
#define TYPEOF(x) &typeid(x)
#define RUNE_METHOD_CALLBACK(method, target) method_info(method, target, #method)
// #define RUNE_LAMBDA_CALLBACK(lambda) 

namespace Rune
{
    #define ASSERT_IS_EVENT(TYPE) static_assert(std::is_base_of<IEvent, TYPE>::value, "Template must be of IEvent")
    typedef const std::type_info* typeOf;

    template<typename Class, typename Args>
    struct method_info
    {
        std::string method_name;
        Class* target;
        void(Class::*method_ptr)(Args);

        method_info(void(Class::*func)(Args), Class* target, std::string func_name)
        {
            method_ptr = func;
            target = target;
            method_name = func_name;

            auto index = method_name.find_last_of("::");
            if(index != -1)
                method_name.erase(0, index+1);
        }
    };

    class EventSystem
    {
    public:
        void test(WindowResizedEvent x) { 
            std::cout << "TESTING! Width: " << x.Width() << ", Height: " << x.Height() << "\n";
        }

        void PollEvents()
        {

            BindMethod(RUNE_METHOD_CALLBACK(&EventSystem::test, this));
            UnbindMethod(RUNE_METHOD_CALLBACK(&EventSystem::test, this));
        }

        EventSystem()
        {
            PollEvents();
        }

        template<typename TEventType, class Class>
        void BindMethod(method_info<Class, TEventType> info)
        {
            auto func = std::bind(info.method_ptr, info.target, std::placeholders::_1);
            EventCallback<TEventType>* evt = new EventCallback<TEventType>(func, info.method_name);
            AddCallback<TEventType>(evt);
        }

        template<typename TEventType, typename Class>
        void UnbindMethod(method_info<Class, TEventType> info)
        {
            std::cout << "Unbinding callback with ID: " << info.method_name << std::endl;
        }

        template<typename TEventType>
        void AddCallback(EventCallback<TEventType>* listener)
        {
            ASSERT_IS_EVENT(TEventType);
            typeOf evtId = TYPEOF(TEventType);
            
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
            typeOf evtId = TYPEOF(TEventType);

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
            typeOf evtId = TYPEOF(TEventType);

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
            typeOf evtId = TYPEOF(TEventType);

            if(_listeners.count(evtId))
                return _listeners.at(evtId).size();

            return 0; 
        }

    private:
        std::map<typeOf, std::vector<IEventCallback*>> _listeners;
    };
}