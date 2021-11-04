#pragma once

#include "../application.h"
#include "../../platforms/window/windowswindow.h"
#include "inputcommand.h"
#include "keys.h"
#include <map>
#include <vector>
#include <string>

class Application;

class InputManager
{
private:
    static inline GLFWwindow* wnd = nullptr;
    static inline std::map<int, std::vector<InputCommand*>> cmds = {};

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
        Window* window = Application::GetWindow();
        WindowsWindow* windowsWindow = static_cast<WindowsWindow*>(window);
        wnd = windowsWindow->GetWindowHandler();

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

    static bool WasKeyPressed(int keycode) {
        return glfwGetKey(wnd, keycode) == GLFW_PRESS;    
    }

    static void HandleInputs() 
    {
        for(const auto& cmd : cmds)
        {
            int keycode = cmd.first;
            std::vector<InputCommand*> commands = cmd.second;

            if(WasKeyPressed(keycode))
                for(const auto& command : commands)
                    command->Execute();
        }
    }
};