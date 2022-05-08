#pragma once

#include "time.h"
#include "platformdetector.h"

#include "api/rendering/window/window.h"
#include "api/filesystem/fileloader.h"
#include "api/input/inputmanager.h"

namespace Rune
{
    class Application 
    {
    private:
        static inline Window* _window = nullptr;
        static inline Time* _time = nullptr;
        Application() { }

        ~Application() {
            delete _window;
            delete _time;
        }

    public:
        static void StartApp(int window_width, int window_height, char* window_name)
        {
            _time = new Time();
            WindowProps props(window_width, window_height, window_name,true);
            Application::_window = Window::Create(props);

            FileLoader::Init();
            InputManager::Init();
        } 

        inline static Window* GetWindow() { return _window; }

        inline static bool Started() { return _window != nullptr; }

        inline static bool ShouldClose() { return _window->ShouldClose(); }

        inline static void Close() { _window->Close(); }

        inline static Time* GetTime() { return _time; }

        static void Update() 
        {
            _window->OnUpdate();
            _time->Update();
        }
    };
}