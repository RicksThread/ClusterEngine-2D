#pragma once
#include <vector>
#include <memory>
#include "../Math/Vector3.hpp"
#include "ConvexSideBase.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		//Contains the information in worldspace about a convex shape
		struct ConvexShapeInfo
		{
			ConvexShapeInfo() : pointsWorldSpace(0), sidesWorldSpace(0) {}

			std::vector<std::shared_ptr<Vector2>> pointsWorldSpace;
			std::vector<std::shared_ptr<ConvexSideBase>> sidesWorldSpace;
			Vector2 center;
			Quaternion rotation;
		};
	}
}