#include "ConvexSide2D.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		ConvexSide2D::ConvexSide2D() {}

		ConvexSide2D::ConvexSide2D(Transform* transformCollider, Vector2 pointA, Vector2 pointB)
		{
			std::vector<Vector3> points;
			points.push_back(MathUtils::ToVec3(pointA));
			points.push_back(MathUtils::ToVec3(pointB));

			data = std::move(std::unique_ptr<Data>(new Data(transformCollider, points)));
		}

		Vector3 ConvexSide2D::GetDirection() const
		{
			return data->points[1] - data->points[0];
		}

		Vector3 ConvexSide2D::GetNormal() const
		{
			Vector3 directionNormalized = Vector3::Normalized(GetDirection());

			//rotate the direction to make it perpendicular to the direction of the side
			Vector3 rotateDir = Quaternion::FromEulerDegree(0, 0, 90) * directionNormalized;
			return rotateDir; //return the normal of the side
		}

		std::shared_ptr<ConvexSideBase> ConvexSide2D::GetWorldSpace() const
		{
			using std::shared_ptr;

			Vector2 pointWorldSpaceA =
				MathUtils::ToVec2(data.get()->transform->PointLocalToWorldSpace(data.get()->points[0]));

			Vector2 pointWorldSpaceB =
				MathUtils::ToVec2(data.get()->transform->PointLocalToWorldSpace(data.get()->points[1]));

			return shared_ptr<ConvexSideBase>(new ConvexSide2D(data->transform, pointWorldSpaceA, pointWorldSpaceB));
		}
	}
}