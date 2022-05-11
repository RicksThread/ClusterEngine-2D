#pragma once
#include "ConvexSideBase.hpp"
#include "../Math/Vector2.hpp"
#include "../Math/MathUtils.hpp"


namespace ClusterEngine
{
	namespace Physics
	{
		//contains side information about the convex poligon
		//it contains the two points of a side in the data
		class ConvexSide2D : public ConvexSideBase
		{
		public:
			ConvexSide2D();
			ConvexSide2D(Transform* colliderTransform, Vector2 pointA, Vector2 pointB);

			virtual Vector3 GetDirection() const override final;

			virtual Vector3 GetNormal() const override final;

			virtual std::shared_ptr<ConvexSideBase> GetWorldSpace() const override final;
		};
	}
}