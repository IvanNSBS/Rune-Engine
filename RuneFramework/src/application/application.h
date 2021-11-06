#pragma once

#include "../platformdetector.h"
#include "../rendering/window/window.h"

#include "../filesystem/fileloader.h"
#include "input/inputmanager.h"

namespace Rune
{
    class Application 
    {
    private:
        static inline Window* _window = nullptr;

        Application() { }

        ~Application() {
            delete _window;
        }

    public:
        static void StartApp(int window_width, int window_height, char* window_name)
        {
            WindowProps props(window_width, window_height, window_name,true);
            Application::_window = Window::Create(props);

            FileLoader::Init();
            InputManager::Init();
        } 

        inline static Window* GetWindow() { return _window; }

        inline static bool Started() { return _window != nullptr; }

        inline static bool ShouldClose() { return _window->ShouldClose(); }

        inline static void Close() { _window->Close(); }

        static void Update() 
        {
            _window->OnUpdate();
        }
    };
}