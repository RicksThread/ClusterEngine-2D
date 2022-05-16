#include <iostream>
#include <math.h>
#include "EngineManager.h"
#include "WindowSettings.h"
#include "GameInitialization.h"


//program entry point
int main()
{
    using namespace ClusterEngine;

    EngineManager::LoadState state;
    std::string operationLog;
    GameInitialization gameInitializer;
    EngineManager::StartApplication(&gameInitializer, &state, &operationLog);
    return 0;
}