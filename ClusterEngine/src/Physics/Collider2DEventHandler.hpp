#pragma once
#include <unordered_set>
#include "Collider2D.hpp"
#include "PhysicsManager.hpp"
#include "PhysicComponent.hpp"
#include "../MultiCastDelegate.hpp"
#include "../Math/MathUtils.hpp"
#include "../GameObject.h"

namespace ClusterEngine
{
	namespace Physics
	{
		class Collider2DEventHandler : public CollisionSyncHandler
		{

		public:
			MultiCastDelegate<void, Collider2D::CollisionInfo&> OnCollisionEnter;
			MultiCastDelegate<void, Collider2D&, Collider2D&> OnCollisionExit;
			MultiCastDelegate<void, Collider2D::CollisionInfo&> OnCollisionStay;

			Collider2DEventHandler(Collider2D* collider);
		protected:
			virtual void Start() override;
			virtual void FixedUpdate() override;
			virtual void CollisionUpdate() override;

		private:
			std::unique_ptr<std::unordered_set<Collider2D*>> collidersColliding;
			std::unique_ptr<std::unordered_set<Collider2D*>> collidersCollidingPrevious;

			std::vector<Collider2D*> collidersCollisionOnExitQueue;
			std::vector<Collider2D::CollisionInfo> collisionInfoCollisionOnEnter;
			std::vector<Collider2D::CollisionInfo> collisionInfoCollisionOnStay;

			Collider2D* currentCollider;
		};
	}
}
