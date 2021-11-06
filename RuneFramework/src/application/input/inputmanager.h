#pragma once

#include "inputcommand.h"
#include "keyboard.h"
#include "mouse.h"
#include "keys.h"
#include <map>
#include <vector>


// TODO: Static class or make it a singleton?
class InputManager
{
private:
    static inline Keyboard* _keyboard = nullptr;
    static inline Mouse* _mouse = nullptr;
    static inline std::map<int, std::vector<InputCommand*>> cmds = {};

    static bool KeyExists(int key);
    static bool CommandExists(InputCommand* cmd, std::vector<InputCommand*>::iterator& it);
public:
    static bool Init();
    static void RegisterCommand(InputCommand* cmd);
    static bool RemoveCommand(InputCommand* cmd);
    static bool SetCommandKey(InputCommand* cmd, int new_key);
    static inline bool IsKeyPressed(int keycode);
    static inline float GetMouseX();
    static inline float GetMouseY();
    static inline glm::vec2 GetMousePosition();
    static inline bool IsMouseButtonDown();
    static void HandleInputs();
};