#pragma once

#include <map>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <type_traits>
#include <memory>
#include "event.h"
#include "eventcallback.h"

#define TYPEOF(x) &typeid(x)

namespace Rune
{
    #define ASSERT_IS_EVENT(TYPE) static_assert(std::is_base_of<IEvent, TYPE>::value, "Template must be of IEvent")
    typedef const std::type_info* typeOf;

    class EventSystem
    {
    public:
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
        inline void Bind(void(Class::*member_func)(TEvt), Class* instance)
        {
            IEventCallback* evt = new MemberFuncCallback<Class, TEvt>(member_func, instance);
            AddCallback<TEvt>(evt);
        }

        template<typename TEvt>
        inline void Bind(void(*foo)(TEvt))
        {
            IEventCallback* clbk = new FuncCallback<TEvt>(foo);
            AddCallback<TEvt>(clbk);
        }

        template<typename TEvt, typename Class>
        inline bool Unbind(void(Class::*member_func)(TEvt), Class* instance)
        {
            std::unique_ptr<IEventCallback> clbk = std::make_unique<MemberFuncCallback<Class, TEvt>>(member_func, instance);
            return RemoveCallback<TEvt>(clbk.get()); 
        }

        template<typename TEvt>
        inline bool Unbind(void(*foo)(TEvt))
        {
            std::unique_ptr<IEventCallback> clbk = std::make_unique<FuncCallback<TEvt>>(foo);
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
                    auto sub = static_cast<BaseEventCallback<TEvt>*>(_listeners.at(evtId).at(i));
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
        void AddCallback(IEventCallback* listener)
        {
            ASSERT_IS_EVENT(TEvt);
            typeOf evtId = TYPEOF(TEvt);
            
            if(_listeners.count(evtId))
                _listeners.at(evtId).push_back(listener);
            else
                _listeners[evtId] = std::vector<IEventCallback*>{listener};
        }

        template<typename TEvt>
        bool RemoveCallback(IEventCallback* listener)
        {
            ASSERT_IS_EVENT(TEvt);
            typeOf evtId = TYPEOF(TEvt);

            bool removed = false;
            if(_listeners.count(evtId))
            {
                std::vector<IEventCallback*>* callbacks = &_listeners.at(evtId);
                for(size_t i = callbacks->size() - 1; i >= 0; i--)
                {
                    if(listener == callbacks->at(i))
                    {
                        IEventCallback* toRemove = callbacks->at(i);
                        callbacks->erase(callbacks->begin() + i);
                        removed = true;

                        delete toRemove;
                        break;
                    }
                }
            }

            return removed;
        }
    };
}