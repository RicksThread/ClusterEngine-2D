#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include "../Math/Vector2.hpp"
#include "../Component.h"
#include "../MultiCastDelegate.h"

namespace ClusterEngine
{
	namespace Physics
	{
		class Collider2DEventHandler;

		//class that handles the intersections between
		//convex shapes and circles

		//base class for all colliders
		class Collider2D : public Component
		{
		public:
			friend class Collider2DEventHandler;

			bool isTriggerer;

			/**
			 * Contains the information of the collision event
			 */
			struct CollisionInfo
			{
				Vector2 collisionPoint;
				Vector2 collisionPoint2;
				bool isColliding;

				float deltaError;
				Vector2 collisionNormal;

				Collider2D* colliderA;
				Collider2D* colliderB;
			};

			Collider2D() = delete;
			Collider2D(bool isTriggerer);

			/**
			 * Checks if this collider is intersecting with another one
			* @param collider: the other collider
			*/
			virtual CollisionInfo Intersect(Collider2D& collider) = 0;

			/**
			 * Checks if the given point is contained withing the collider shape
			* @param point: The point to check if contained
			*/
			virtual bool Contains(Vector2 point) = 0;

			/**
			 * Returns the square distance over which is impossible to collide with this collider (dst of the furthest points of the collider)
			*/
			virtual float GetEffectiveRange() const = 0;

			~Collider2D();

		protected:

			virtual void Update() = 0;
			virtual void Start() = 0;


			static std::vector<Collider2D*> colliders;
		};
	}
}