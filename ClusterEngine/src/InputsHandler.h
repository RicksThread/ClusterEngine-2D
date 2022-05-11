#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include <iostream>
#include "Math\Vector2.hpp"

namespace ClusterEngine
{
    class EngineManager;

    class InputsHandler
    {
    public:
        //returns true if the key is pressed
        inline static bool GetInput(int key);

        //returns true if the key has just been pressed
        inline static bool GetInputDown(int key);

        //returns true if the key has just been released
        inline static bool GetInputUp(int key);

        inline static bool GetInputMouseUp(int key);

        inline static bool GetInputMouseDown(int key);

        inline static bool GetInputMouse(int key);

        //returns the pixel position of the cursor
        inline static Vector2 GetMousePosition();
    private:
        friend class EngineManager;

        struct Input
        {
            bool pressedDown = false;
            bool isPressing = false;
            bool pressedUp = false;
        };

        static Vector2 mousePosition;

        //keys currently being pressed
        static std::map<int, Input> activeKeys;
        static std::map<int, Input> activeMouseButtons;

        //callback for the input events
        static void ProcessInputKeys(GLFWwindow* window, int key, int scanCode, int action, int mods);
        static void ProcessInputMouseButtons(GLFWwindow* window, int button, int action, int mods);
        static void ProcessInput(std::map<int, Input>& activeInputs, int index, int action);
        
        static void TickUpdate();
        static void TickInputs(std::map<int, Input>& activeInputs);
    };

    bool InputsHandler::GetInput(int key)
    {
        if (!activeKeys.count(key))
            return false;
        return true;
    }

    bool InputsHandler::GetInputDown(int key)
    {
        if (!activeKeys.count(key))
            return false;

        return activeKeys[key].pressedDown;
    }

    bool InputsHandler::GetInputUp(int key)
    {
        if (!activeKeys.count(key))
            return false;

        return activeKeys[key].pressedUp;
    }

    bool InputsHandler::GetInputMouse(int button)
    {
        if (!activeMouseButtons.count(button))
            return false;
        return true;
    }

    bool InputsHandler::GetInputMouseDown(int button)
    {
        if (!activeMouseButtons.count(button))
            return false;

        return activeMouseButtons[button].pressedDown;
    }

    bool InputsHandler::GetInputMouseUp(int button)
    {
        if (!activeMouseButtons.count(button))
            return false;

        return activeMouseButtons[button].pressedUp;
    }

    Vector2 InputsHandler::GetMousePosition()
    {
        return mousePosition;
    }
}

