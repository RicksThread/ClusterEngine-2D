#pragma once
#include <vector>
#include "PhysicsManager.hpp"
#include "CollisionSyncHandler.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		class CollisionManager
		{
		private:
			friend class PhysicsManager;
			friend class CollisionSyncHandler;

			static void CollisionsTick();
		};
	}
}