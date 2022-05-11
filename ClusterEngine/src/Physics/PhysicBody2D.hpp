
#pragma once

#include "PhysicsManager.hpp"
#include "Collider2DEventHandler.hpp"
#include "../Math/Vector3.hpp"
#include "../InputsHandler.h"

namespace ClusterEngine
{
	namespace Physics
	{
		class PhysicBody2D : public Collider2DEventHandler
		{
		public:
			enum class Interpolation { NONE, INTERPOLATE };
			enum ForceMode2D { FORCE, IMPULSE, ACCELERATION, CHANGEVELOCITY };

			Interpolation interpolation;

			float mass;
			float drag;
			float gravity = 9.8f;

			PhysicBody2D(Collider2D* collider, float mass, float drag);

			void AddForce(Vector2 force, ForceMode2D forceMode);

			inline Vector2 GetVelocity() const;

		protected:

			virtual void Start() override;
			virtual void Update() override;
			virtual void FixedUpdate() override;
			void CollisionPhysic(Collider2D::CollisionInfo& info);

		private:
			friend class PhysicBody2D;
			Vector2 velocity;
			std::unordered_set<PhysicBody2D*> bodiesCollided;

			void HandleDrag();
			void HandleGravity();
		};
	}
}