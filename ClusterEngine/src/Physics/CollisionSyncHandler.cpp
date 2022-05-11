#include "CollisionSyncHandler.hpp"
#include <iostream>

namespace ClusterEngine
{
	namespace Physics
	{
		std::vector<CollisionSyncHandler*> CollisionSyncHandler::collisionSyncHandlers(0);

		CollisionSyncHandler::CollisionSyncHandler()
		{
			//When the instancing the collisionSyncHandler is inserted in the vector
			collisionSyncHandlers.push_back(this);
		}

		CollisionSyncHandler::~CollisionSyncHandler()
		{
			//On dispose it removes this collisionSyncHandler from the vector
			auto it = std::remove(collisionSyncHandlers.begin(), collisionSyncHandlers.end(), this);
			collisionSyncHandlers.erase(it);
		}
	}
}