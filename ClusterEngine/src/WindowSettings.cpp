#include "WindowSettings.h"

namespace ClusterEngine
{
    MultiCastDelegate<void, float, float> WindowSettings::OnWindowSizeModified;
    GLFWwindow* WindowSettings::mainWindow;

    int WindowSettings::width = 1080;
    int WindowSettings::height = 720;
    int WindowSettings::cameraSize = 5;

    int WindowSettings::GetWidth()
    {
        return width;
    }

    int WindowSettings::GetHeight()
    {
        return height;
    }

    int WindowSettings::GetCameraSize()
    {
        return cameraSize;
    }

    void WindowSettings::Framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
    {
        glViewport(0, 0, _width, _height);
        width = _width;
        height = _height;
        OnWindowSizeModified.Invoke(_width, _height);
    }

    void WindowSettings::SetWindowSize(int _width, int _height)
    {
        glfwSetWindowSize(mainWindow, _width, _height);
    }

    void WindowSettings::Init(GLFWwindow* window)
    {
        mainWindow = window;
    }
}