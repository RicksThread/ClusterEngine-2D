#pragma once

#include "PhysicComponent.hpp"
#include <vector>
#include <memory>
#include "../Component.h"
#include "../MultiCastDelegate.hpp"
#include "../EngineTime.hpp"
#include "../Math/MathUtils.hpp"
#include "CollisionManager.hpp"
#include "../GameObject.h"

namespace ClusterEngine
{
	class EngineManager;
	namespace Physics
	{

		class PhysicsManager
		{
		public:

			static float GetFixedDeltaTime() noexcept;
			static float GetStepFixedUpdate() noexcept;
		private:

			static float fixedDeltaTime;
			static float previousTime;
			static constexpr float waitTime = 0.02f;
			static void Tick();

			friend EngineManager;
		};
	}
}