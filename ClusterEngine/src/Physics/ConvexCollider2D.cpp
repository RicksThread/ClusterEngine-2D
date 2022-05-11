#include "ConvexCollider2D.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		ConvexCollider2D::ConvexCollider2D(bool isTriggerer) : Collider2D(isTriggerer)
		{
		}

		ConvexCollider2D::ConvexCollider2D(bool isTriggerer, const std::vector<Vector2>& points) : static_points(points), sqrMaxDstPoint(0), Collider2D(isTriggerer)
		{
		}

		void ConvexCollider2D::Start()
		{
			using std::unique_ptr;

			//initialize the vector of sides 
			//NOTE: it must be done on start because the transform is not ready when the constructor is called
			for (int i = 0; i < sides.size() - 1; ++i)
			{
				sides.push_back(unique_ptr<ConvexSideBase>(new ConvexSide2D(GetTransform(), static_points[i], static_points[i])));
			}

			//connect the last point of the array to the first to close the polygon
			int lastIndex = sides.size() - 1;
			sides.push_back(unique_ptr<ConvexSideBase>(new ConvexSide2D(GetTransform(), static_points[lastIndex], static_points[0])));

			sqrMaxDstPoint = GetMaxDstPoints(static_points);
		}

		float ConvexCollider2D::GetMaxDstPoints(const std::vector<Vector2>& points)
		{
			float maxDstPoint = 0;
			for (const auto& point : static_points)
			{
				float currentDst = Vector2::Magnitude(point * MathUtils::ToVec2(GetTransform()->scale));
				if (maxDstPoint < currentDst)
				{
					maxDstPoint = currentDst;
				}
			}
			return maxDstPoint;
		}

		ConvexShapeInfo ConvexCollider2D::GetConvexColliderWSInfo()
		{
			ConvexShapeInfo shapeInfo;

			//convert all the points in worldspace
			for (int i = 0; i < sides.size(); ++i)
			{
				shapeInfo.sidesWorldSpace.push_back(sides[i].get()->GetWorldSpace());
			}

			for (int i = 0; i < static_points.size(); i++)
			{
				shapeInfo.pointsWorldSpace.push_back
				(
					std::shared_ptr<Vector2>(new Vector2(MathUtils::ToVec2(gmObj->transform->PointLocalToWorldSpace(MathUtils::ToVec3(static_points[i])))))
				);
			}

			shapeInfo.center = MathUtils::ToVec2(GetTransform()->position);
			shapeInfo.rotation = gmObj->transform->rotation;

			return shapeInfo;
		}

		Collider2D::CollisionInfo ConvexCollider2D::Intersect(Collider2D& collider)
		{

			if (dynamic_cast<ConvexCollider2D*>(&collider) != nullptr)
			{
				ConvexCollider2D* convexCollider = dynamic_cast<ConvexCollider2D*>(&collider);

				ConvexShapeInfo otherColliderSides = convexCollider->GetConvexColliderWSInfo();
				ConvexShapeInfo currentColliderSides = GetConvexColliderWSInfo();

				ProjectionCollider projCollider(currentColliderSides, otherColliderSides);
				projCollider.Project();

				//create the data info about the collision

				CollisionInfo info;
				info.collisionPoint = projCollider.collisionPoint;
				info.collisionPoint2 = projCollider.collisionPoint2;
				info.isColliding = projCollider.GetIsColliding();
				info.colliderA = this;
				info.colliderB = &collider;
				info.deltaError = projCollider.deltaCollision;
				info.collisionNormal = projCollider.collisionNormal;
				return info;
				//estract the projection information
			}
		}

		bool ConvexCollider2D::Contains(Vector2 point)
		{
			return false;
		}

		float ConvexCollider2D::GetEffectiveRange() const
		{
			return sqrMaxDstPoint;
		}
	}
}