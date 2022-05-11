#pragma once
#include <vector>
#include <climits>
#include <functional>
#include <memory>
#include "../Math/MathUtils.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		class ConvexCollider2D;
		struct ConvexShapeInfo;

		class ProjectionCollider
		{
		public:
			/**
			* 	Contains the value on the plane of the projection and its corresponding point in worldspace
			*/
			struct ShadowPoint
			{
				float value;
				std::vector<Vector2> points;
			};

			class ShadowProjection
			{
			public:
				ShadowPoint minPoint;
				ShadowPoint maxPoint;

				static ShadowProjection GetDefaultProjection() ;

				/**
					Takes control of the shadow point to recalculate the projection of the figure on the axis plane
				 */
				void Take(ShadowPoint& shadow);

				/**
		   			Returns the shadow "A" if the checker is true, B otherwise, but if the 2 are equal in values then they'll be summed
     	  			@param aShadow: first param to check
					@param bShadow: second param to check
					@param checker: function that'll confront the first and second shadow, if true it'll return the aShadow
				 */
				ShadowPoint GetShadowOnCondition(ShadowPoint& aShadow, ShadowPoint& bShadow, std::function<bool(float,float)> checker) const;

				/**
				 * 	The avg point of the min and max of the projection
				 */
				inline float CenterPointValue() const;

				/**
				 * 	Distance of the min and max, (the length of the shadow)
				 */
				inline float GetLength() const;
			private:

				//utility functions for the checker

				ShadowPoint GetShadowPointMax(ShadowPoint& aShadow, ShadowPoint& bShadow);

				ShadowPoint GetShadowPointMin(ShadowPoint& aShadow, ShadowPoint& bShadow);
			};



			/**
			 * 	Helper class that calculates the intersection values of the shadow projections
			 */
			class ShadowIntersection
			{
			public:
		
				//calculated closest points
				ShadowPoint closestPointA;
				ShadowPoint closestPointB;
		

				ShadowIntersection() = default;
				ShadowIntersection(ShadowProjection& projA, ShadowProjection& projB) : projA(projA), projB(projB), isColliding(false) {}

				/**
				 * Calculates the projection data and stores in the object
				 */
				void IntersectProjection();

				inline bool GetIsColliding() const;

				inline float GetDstValueClosestPoints() const;

			private:
				ShadowProjection projA;
				ShadowProjection projB;
				bool isColliding;
			};

			ProjectionCollider(ConvexShapeInfo& a, ConvexShapeInfo& b);

			/**
			 * Computes the projection and calculates the most likely collision point
			*/
			void Project();

			bool GetIsColliding() const;

			Vector2 collisionPoint;
			Vector2 collisionPoint2;
			float deltaCollision;
			Vector2 collisionNormal;
		private:
			bool isColliding;
			ConvexShapeInfo& shapeColliderA;
			ConvexShapeInfo& shapeColliderB;

			Vector2 ToColliderSpace(const Vector2& colliderPoint);

			ShadowProjection GetColliderShadowProjection(const std::vector<std::shared_ptr<Vector2>> points, Vector2 axis);

		};

	}
}