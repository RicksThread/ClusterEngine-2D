#pragma once
#include <vector>
#include "../Transform.h"
#include <memory>

namespace ClusterEngine
{
	namespace Physics
	{
		class ConvexSideBase
		{
		public:
			struct Data
			{
				Transform* transform;
				std::vector<Vector3> points;

				Data(Transform* transform, std::vector<Vector3>& points) : transform(transform), points(points) {}

				Data(Transform* transform, Vector3 points[], int dim) : transform(transform), points(points, points + dim) {}
			};

			std::unique_ptr<Data> data;

			ConvexSideBase() : data(nullptr) {}
			ConvexSideBase(Data* data) : data(data) {}

			virtual Vector3 GetDirection() const = 0;

			/**
			 * Returns the normal of the side
			*/
			virtual Vector3 GetNormal() const = 0;

			virtual std::shared_ptr<ConvexSideBase> GetWorldSpace() const = 0;
		};
	}
}
