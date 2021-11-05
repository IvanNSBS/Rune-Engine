#pragma once

#include "../platformdetector.h"
#include "../rendering/window/window.h"

#include "../filesystem/fileloader.h"
#include "input/inputmanager.h"


// TODO: Application Class shouldn't need to include platform specific stuff
#include "../rendering/window/windows/windowswindow.h"

class Application 
{
private:
    static inline Window* _window = nullptr;
    // static inline InputManager* _inputmanager = nullptr;

    Application() { }

    ~Application() {
        delete _window;
    }

public:
    static void StartApp(int window_width, int window_height, char* window_name)
    {
        // TODO: Add IFDEF clauses to switch between API and Window Contexts
        #ifdef RUNE_PLATFORM_WINDOWS
        Application::_window = new WindowsWindow(window_name, window_width, window_height);
        #endif
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