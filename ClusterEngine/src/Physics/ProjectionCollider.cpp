#include "ProjectionCollider.hpp"

#include "ConvexCollider2D.hpp"
#include "../Utilities.h"

namespace ClusterEngine
{
	namespace Physics
	{
		ProjectionCollider::ShadowProjection ProjectionCollider::ShadowProjection::GetDefaultProjection()
		{
			ShadowProjection shadowProjection;

			shadowProjection.maxPoint.value = -FLOAT_MAX;

			shadowProjection.minPoint.value = FLOAT_MAX;

			return shadowProjection;
		}

		void ProjectionCollider::ShadowProjection::Take(ShadowPoint& shadow)
		{

			//automatically sorts out the min and max with the new given shadowpoint
			maxPoint = GetShadowPointMax(shadow, maxPoint);

			minPoint = GetShadowPointMin(shadow, minPoint);

		}

		ProjectionCollider::ShadowPoint ProjectionCollider::ShadowProjection::GetShadowOnCondition
		(
			ProjectionCollider::ShadowPoint& aShadow,
			ProjectionCollider::ShadowPoint& bShadow,
			std::function<bool(float, float)> checker
		) const
		{

			//if it returns true then a will be returned

			if (aShadow.value == bShadow.value)
			{
				aShadow.points.insert(aShadow.points.end(), bShadow.points.begin(), bShadow.points.end());
				return aShadow;
			}
			if (checker(aShadow.value, bShadow.value))
			{
				return aShadow;
			}
			else
			{
				return bShadow;
			}
		}

		float ProjectionCollider::ShadowProjection::CenterPointValue() const
		{
			return (minPoint.value + maxPoint.value) * 0.5f;
		}

		float ProjectionCollider::ShadowProjection::GetLength() const
		{
			return std::abs(maxPoint.value - minPoint.value);
		}

		ProjectionCollider::ShadowPoint ProjectionCollider::ShadowProjection::GetShadowPointMax(ProjectionCollider::ShadowPoint& aShadow, ProjectionCollider::ShadowPoint& bShadow)
		{
			auto maxShadowPointGetter([](float a, float b) {return a > b; });
			return GetShadowOnCondition(aShadow, bShadow, maxShadowPointGetter);
		}

		ProjectionCollider::ShadowPoint ProjectionCollider::ShadowProjection::GetShadowPointMin(ProjectionCollider::ShadowPoint& aShadow, ProjectionCollider::ShadowPoint& bShadow)
		{
			auto minShadowPointGetter([](float a, float b) {return a < b; });
			return GetShadowOnCondition(aShadow, bShadow, minShadowPointGetter);
		}



		void ProjectionCollider::ShadowIntersection::IntersectProjection()
		{
			using std::cout;
			float AToB = projA.CenterPointValue() - projB.CenterPointValue();


			if (std::abs(AToB) > (projA.GetLength() * .5f + projB.GetLength() * .5f))
			{
				isColliding = false;
			}
			else
			{

				//if the figures are overlapping
				isColliding = true;

				//if the A figure is at the right of the b figure
				if (AToB < 0)
				{
					closestPointA = projA.maxPoint;
					closestPointB = projB.minPoint;
				}
				else
				{
					closestPointA = projA.minPoint;
					closestPointB = projB.maxPoint;
				}
			}
		}

		bool ProjectionCollider::ShadowIntersection::GetIsColliding() const
		{
			return isColliding;
		}

		float ProjectionCollider::ShadowIntersection::GetDstValueClosestPoints() const
		{
			return std::abs(closestPointA.value - closestPointB.value);
		}



		ProjectionCollider::ProjectionCollider(ConvexShapeInfo& a, ConvexShapeInfo& b)
			: shapeColliderA(a), shapeColliderB(b), collisionPoint(Vector2::Zero()), isColliding(false)
		{}

		//i cried so much doing this
		void ProjectionCollider::Project()
		{
			using std::abs;
			using std::cout;
			using std::min;

			isColliding = true;
			float closestPointsDst = INT_MAX;

			int sidesColliderACount = shapeColliderA.sidesWorldSpace.size();
			int sidesColliderBCount = shapeColliderB.sidesWorldSpace.size();
			int totalSidesLength = sidesColliderACount + sidesColliderBCount;


			ShadowIntersection targetIntersection;
			Vector2 targetAxisPlane;
			//iterate through all the sides' normal
			for (int i = 0; i < totalSidesLength; ++i)
			{
				//create the axis and shadowIntersection for the given axis
				Vector2 normalAxisPlane;

				if (i < sidesColliderACount)
					normalAxisPlane = MathUtils::ToVec2(shapeColliderA.sidesWorldSpace[i].get()->GetNormal());
				else
					normalAxisPlane = MathUtils::ToVec2(shapeColliderB.sidesWorldSpace[i - sidesColliderACount].get()->GetNormal());
				//put as a reference the center of the collider A
				//check for border limits of the first collider on the current projection axis
				ShadowProjection projectionColliderA = GetColliderShadowProjection(shapeColliderA.pointsWorldSpace, normalAxisPlane);

				//check for border limits of the second collider on the current projection axis
				ShadowProjection projectionColliderB = GetColliderShadowProjection(shapeColliderB.pointsWorldSpace, normalAxisPlane);

				//loads shadowIntersection
				ShadowIntersection shadowIntersection(projectionColliderA, projectionColliderB);
				shadowIntersection.IntersectProjection();

				if (!shadowIntersection.GetIsColliding())
				{
					isColliding = false;
					collisionPoint = Vector2::Zero();
					break;
				}
				else
				{
					float currentPointsDst = shadowIntersection.GetDstValueClosestPoints();

					//if the projections are colliding then check the closest points
					if (currentPointsDst < closestPointsDst)
					{
						targetIntersection = shadowIntersection;
						targetAxisPlane = normalAxisPlane;

						closestPointsDst = currentPointsDst;
					}
				}
			}

			if (isColliding)
			{
				//configure the collision point
				float perpendicularLineValue;
				if (targetIntersection.closestPointB.points.size() > 1)
				{
					//if B is perpendicular to the plane
					perpendicularLineValue = targetIntersection.closestPointB.value;
					deltaCollision = abs(perpendicularLineValue - targetIntersection.closestPointA.value);
					collisionPoint = targetIntersection.closestPointA.points[0];
				}
				else
				{
					//if A is perpendicular to the plane
					perpendicularLineValue = targetIntersection.closestPointA.value;
					deltaCollision = abs(perpendicularLineValue - targetIntersection.closestPointB.value);
					collisionPoint = targetIntersection.closestPointB.points[0];
				}

				//the perpendicular line has to always be positive
				//if not then invert the max and min shadow point
				if (perpendicularLineValue < 0)
				{
					targetAxisPlane = -targetAxisPlane;
				}



				collisionNormal = targetAxisPlane;
			}
		}

		ProjectionCollider::ShadowProjection ProjectionCollider::GetColliderShadowProjection(const std::vector<std::shared_ptr<Vector2>> points, Vector2 axis)
		{
			ShadowProjection projectionCollider = ShadowProjection::GetDefaultProjection();

			for (int i = 0; i < points.size(); i++)
			{
				ShadowPoint shadowPoint;

				//convert the points in collider space
				shadowPoint.points.push_back(*points[i].get());
				shadowPoint.value = Vector2::Dot(axis, ToColliderSpace(shadowPoint.points[0]));

				//get value position in the projection of both of the pointss
				projectionCollider.Take(shadowPoint);
			}
			return projectionCollider;
		}

		Vector2 ProjectionCollider::ToColliderSpace(const Vector2& colliderPoint)
		{
			return colliderPoint - shapeColliderB.center;
		}

		bool ProjectionCollider::GetIsColliding() const
		{
			return isColliding;
		}
	}
}