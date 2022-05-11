#include "PhysicsManager.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		float PhysicsManager::fixedDeltaTime(waitTime);
		float PhysicsManager::previousTime(0);

		void PhysicsManager::Tick()
		{
			if ((EngineTime::GetTime() - previousTime) >= waitTime)
			{
				fixedDeltaTime = (EngineTime::GetTime() - previousTime);

				previousTime = (float)EngineTime::GetTime();


				for (const auto& pComponent : PhysicComponent::physicComponents)
				{
					if (pComponent->gmObj->hasStarted())
						pComponent->FixedUpdate();
				}
				CollisionManager::CollisionsTick();

			}
		}

		float PhysicsManager::GetFixedDeltaTime() noexcept
		{
			return fixedDeltaTime;
		}

		float PhysicsManager::GetStepFixedUpdate() noexcept
		{
			return MathUtils::Clamp01((EngineTime::GetTime() - previousTime) / waitTime);
		}
	}
}