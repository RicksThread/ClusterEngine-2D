#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MultiCastDelegate.h"

namespace ClusterEngine
{
    class EngineManager;

    class WindowSettings
    {
    public:
        static MultiCastDelegate<void, float, float> OnWindowSizeModified;

        static int GetWidth();
        static int GetHeight();
        static int GetCameraSize();
        static void SetWindowSize(int _width, int _height);

    private:
        friend class EngineManager;

        static GLFWwindow* mainWindow;
        static int height;
        static int width;
        static int cameraSize;

        static void Init(GLFWwindow* mainWindow);
        static void Framebuffer_size_callback(GLFWwindow* window, int width, int height);
    };
}