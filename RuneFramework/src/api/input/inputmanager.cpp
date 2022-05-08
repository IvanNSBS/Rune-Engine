#pragma once

#include "./inputmanager.h"
#include "api/application.h"

namespace Rune
{
    bool InputManager::KeyExists(int key)
    {
        if(cmds.find(key) == cmds.end())
            return false;

        return true;
    }

    bool InputManager::CommandExists(InputCommand* cmd, std::vector<InputCommand*>::iterator& it) 
    {
        int key = cmd->GetKey();
        if(!KeyExists(key))
            return false;

        it = std::find(cmds[key].begin(), cmds[key].end(), cmd);
        if(it == cmds[key].end())
            return false;

        return true;
    }

    bool InputManager::Init()
    {
        // TODO: Input Manager shouldn't be responsible for
        // instantiating platform specific handlers;
        _keyboard = Keyboard::Create();
        cmds.clear();

        return true;
    }

    void InputManager::RegisterCommand(InputCommand* cmd) {
        cmds[cmd->GetKey()].push_back(cmd);
    }

    bool InputManager::RemoveCommand(InputCommand* cmd) 
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

    bool InputManager::SetCommandKey(InputCommand* cmd, int new_key) 
    {
        bool removed = RemoveCommand(cmd);
        
        if(!removed)
            return false;

        cmd->SetKey(new_key);
        RegisterCommand(cmd);
        return true;
    }

    inline bool InputManager::IsKeyPressed(int keycode) {
        return _keyboard->IsKeyDown(keycode);
    }

    inline float InputManager::GetMouseX() {
        return 0;
    }

    inline float InputManager::GetMouseY() {
        return 0;
    }

    inline glm::vec2 InputManager::GetMousePosition() {
        return glm::vec2(0, 0);
    }

    inline bool InputManager::IsMouseButtonDown() {
        return false;
    }

    void InputManager::HandleInputs() 
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
}