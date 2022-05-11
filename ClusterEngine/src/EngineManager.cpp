#include "EngineManager.h"

namespace ClusterEngine
{
    bool EngineManager::isOpen = false;


    void EngineManager::StartApplication(ClusterEngine::InitHandler* initializationHandler, LoadState* state, std::string* operationLog)
    {
        //initialize glfw
        glfwInit();

        //set the target version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //create the window and set the context thread
        GLFWwindow* window = glfwCreateWindow(600, 600, "ClusterEngine", NULL, NULL);


        if (window == NULL)
        {
            glfwTerminate();
            *state = LoadState::FAIL;
            *operationLog = "Failed to create GLFW Window\n";
            return;
        }
        glfwMakeContextCurrent(window);

        //load glad and check if the process was successful
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            *state = LoadState::FAIL;
            *operationLog = "Error! System couldn't load glad!\n";
            return;
        }


        if (isOpen) return;
        isOpen = true;

        //set the starting settings of the info for the window
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        WindowSettings::Init(window);
        WindowSettings::Framebuffer_size_callback(window, width, height);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0, 1.0);
        //set the input and framebuffer size 
        glfwSetFramebufferSizeCallback(window, WindowSettings::Framebuffer_size_callback);
        glfwSetKeyCallback(window, InputsHandler::ProcessInputKeys);
        glfwSetMouseButtonCallback(window, InputsHandler::ProcessInputMouseButtons);

        StandardShaders::Initialize();

        SceneManager::Init(initializationHandler);
        Sprite::SetIsFlipped(true);
        EngineTime::Update();
        Physics::PhysicsManager::Tick();

        SceneManager::LoadScene(0);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            EngineTime::Update();
            SceneManager::Update();

            if (InputsHandler::GetInputDown(GLFW_KEY_ESCAPE))
            {
                glfwSetWindowShouldClose(window, true);
            }

            Physics::PhysicsManager::Tick();
            SceneManager::RenderUpdate();
            InputsHandler::TickUpdate();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        SceneManager::Terminate();
        glfwTerminate();
    }
}