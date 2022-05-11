#include "InputsHandler.h"

namespace ClusterEngine
{
    std::map<int, InputsHandler::Input> InputsHandler::activeKeys;
    std::map<int, InputsHandler::Input> InputsHandler::activeMouseButtons;

    Vector2 InputsHandler::mousePosition;

    void InputsHandler::ProcessInputKeys(GLFWwindow* window, int key, int scanCode, int action, int mods)
    {
        ProcessInput(activeKeys, key, action);
    }

    void InputsHandler::ProcessInputMouseButtons(GLFWwindow* window, int buttonIndex, int action, int mods)
    {
        ProcessInput(activeMouseButtons, buttonIndex, action);
    }
    
    void InputsHandler::ProcessInput(std::map<int, Input>& activeInputs, int index, int action)
    {
        //input action (pressed or released)
        InputsHandler::Input input;
        switch (action)
        {
        case GLFW_PRESS:
            //add to the map the current active key
            input.isPressing = true;
            input.pressedDown = true;
            input.pressedUp = false;

            activeInputs.insert(std::pair<int, Input>(index, input));
            break;
        case GLFW_RELEASE:
            //warn that the key is pressed up and ready to be deactivated
            activeInputs[index].pressedUp = true;
            break;
        default:
            break;
        }
    }

    void InputsHandler::TickUpdate()
    {
        glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.X, &mousePosition.Y);

        TickInputs(activeKeys);
        TickInputs(activeMouseButtons);
    }

    void InputsHandler::TickInputs(std::map<int, Input>& activeInputs)
    {
        if (activeInputs.size() <= 0) return;
        //container of indices of keys to be discarded
        std::vector<int> inputsToRemove(0);

        //iterate and set the state of the keys
        for (auto const& input : activeInputs)
        {
            if (input.second.pressedDown)
                activeInputs[input.first].pressedDown = false;
            if (input.second.pressedUp)
                inputsToRemove.push_back(input.first);
        }


        for (auto const& index : inputsToRemove)
        {
            activeInputs.erase(index);
        }
    }

}