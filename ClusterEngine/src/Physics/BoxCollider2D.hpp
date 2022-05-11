#pragma once
#include "ConvexCollider2D.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		class BoxCollider2D : public ConvexCollider2D
		{
		public:
			using ConvexCollider2D::sides;
			using ConvexCollider2D::static_points;

			BoxCollider2D(Vector2 size);
			BoxCollider2D(bool isTriggerer, Vector2 size);

		protected:
			virtual void Update() override {}
			virtual void Start() override;
		};
	}
}