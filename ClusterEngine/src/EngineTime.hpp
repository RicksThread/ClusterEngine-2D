#pragma once
#include <GLFW/glfw3.h>
#include <limits>

namespace ClusterEngine
{
	class EngineManager;

	class EngineTime
	{
	public:
		inline static float GetDeltaTime() noexcept { return deltaTime; }
		inline static float GetTime() noexcept { return time; }
		inline static int GetFrameCount() noexcept { return frameCount; }
		inline static float GetFrameRate() noexcept { return frameRate; }
	private:
		friend class EngineManager;

		static float deltaTime;
		static int frameCount;

		static float time;
		static float previousTime;
		static float frameRate;

		static void Update();
	};
}