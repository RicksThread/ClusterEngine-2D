#include "CollisionManager.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		void CollisionManager::CollisionsTick()
		{

			for (auto& collisionSyncHandler : CollisionSyncHandler::collisionSyncHandlers)
			{
				if (collisionSyncHandler->gmObj->hasStarted())
				{
					collisionSyncHandler->CollisionUpdate();
				}
			}
		}
	}
}