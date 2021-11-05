#pragma once

#include "../application.h"
#include "inputcommand.h"
#include "keys.h"
#include <map>
#include <vector>
#include <string>


// #include "keyboard.h"
#include "mouse.h"

// TODO: Platform specific stuff shouldn't be in this header
// This is also preventing initializing the input manager through
// application.h because of a circular dependency, altough it can be
// fixed by using the .cpp file
#include "./windows/windowskeyboard.h"

// TODO: Static class or make it a singleton?
class InputManager
{
private:
    static inline Keyboard* _keyboard = nullptr;
    static inline Mouse* _mouse = nullptr;
    static inline std::map<int, std::vector<InputCommand*>> cmds = {};

    static inline GLFWwindow* wnd = nullptr;
    

    static bool KeyExists(int key)
    {
        if(cmds.find(key) == cmds.end())
            return false;

        return true;
    }

    static bool CommandExists(InputCommand* cmd, std::vector<InputCommand*>::iterator& it) 
    {
        int key = cmd->GetKey();
        if(!KeyExists(key))
            return false;

        it = std::find(cmds[key].begin(), cmds[key].end(), cmd);
        if(it == cmds[key].end())
            return false;

        return true;
    }

public:
    static bool Init()
    {
        // TODO: Input Manager shouldn't be responsible for
        // instantiating platform specific handlers;
        _keyboard = new WindowsKeyboard();
        cmds.clear();

        return true;
    }

    static void RegisterCommand(InputCommand* cmd) {
        cmds[cmd->GetKey()].push_back(cmd);
    }

    static bool RemoveCommand(InputCommand* cmd) 
    {
        std::vector<InputCommand*>::iterator it;
        bool exists = CommandExists(cmd, it);
        
        if(!exists)
            return false;

        int key = cmd->GetKey();
        cmds[key].erase(it);

        if(cmds[key].size() == 0)
            cmds.erase(key);
        
        return true;
    }

    static bool SetCommandKey(InputCommand* cmd, int new_key) 
    {
        bool removed = RemoveCommand(cmd);
        
        if(!removed)
            return false;

        cmd->SetKey(new_key);
        RegisterCommand(cmd);
        return true;
    }

    static inline bool IsKeyPressed(int keycode) {
        return _keyboard->IsKeyDown(keycode);
    }

    static inline float GetMouseX() {
        return 0;
    }

    static inline float GetMouseY() {
        return 0;
    }
    
    static inline glm::vec2 GetMousePosition() {
        return glm::vec2(0, 0);
    }

    static inline bool IsMouseButtonDown() {
        return false;
    }

    static void HandleInputs() 
    {
        for(const auto& cmd : cmds)
        {
            int keycode = cmd.first;
            std::vector<InputCommand*> commands = cmd.second;

            if(IsKeyPressed(keycode))
                for(const auto& command : commands)
                    command->Execute();
        }
    }
};