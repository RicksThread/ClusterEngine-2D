#include "EngineTime.hpp"

namespace ClusterEngine
{
	float EngineTime::deltaTime = 0;
	int EngineTime::frameCount = 0;
	float EngineTime::time = 0;
	float EngineTime::previousTime = 0;
	float EngineTime::frameRate = 0;

	void EngineTime::Update()
	{
		frameCount++;
		time = static_cast<float>(glfwGetTime());
		deltaTime = time - previousTime;
		previousTime = time;

		frameRate = 1.0f / (deltaTime + std::numeric_limits<float>::epsilon());
	}
}