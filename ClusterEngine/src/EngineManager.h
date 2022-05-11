#pragma once
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include "SceneManager.h"
#include "Sprite.hpp"
#include "Math/Math.h"
#include "WindowSettings.h"
#include "InputsHandler.h"
#include "Time.h"
#include "StandardShaders.h"
#include "Physics/PhysicsManager.hpp"

namespace ClusterEngine
{
	class EngineManager
	{
	public:
		static constexpr const char* Version = "1.0";
		static constexpr const char* NameWindow = "ClusterEngine";

		enum class LoadState { SUCCESS, FAIL };

		static void StartApplication(InitHandler* initializationHandler, LoadState* state, std::string* operationLog);
	private:
		static bool isOpen;
	};
}