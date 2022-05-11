#pragma once
#include "PhysicComponent.hpp"
#include "../GameObject.h"
#include <vector>


namespace ClusterEngine
{
	namespace Physics
	{
		class CollisionSyncHandler : public PhysicComponent
		{
		public:
			CollisionSyncHandler();
			~CollisionSyncHandler();

		protected:
			friend class CollisionManager;
			static std::vector<CollisionSyncHandler*> collisionSyncHandlers;
			
			virtual void CollisionUpdate() {}
		};
	}
}