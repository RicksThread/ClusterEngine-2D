#include "BoxCollider2D.hpp"
#include "ProjectionCollider.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		BoxCollider2D::BoxCollider2D(Vector2 size) : ConvexCollider2D(false)
		{
			static_points.push_back(-size * 0.5f);
			static_points.push_back(Vector2(-size.X * 0.5f, size.Y * 0.5f));
			static_points.push_back(size * 0.5f);
			static_points.push_back(Vector2(size.X * 0.5f, -size.Y * 0.5f));
		}

		BoxCollider2D::BoxCollider2D(bool isTriggerer, Vector2 size) : ConvexCollider2D(isTriggerer)
		{
			static_points.push_back(-size * 0.5f);
			static_points.push_back(Vector2(-size.X * 0.5f, size.Y * 0.5f));
			static_points.push_back(size * 0.5f);
			static_points.push_back(Vector2(size.X * 0.5f, -size.Y * 0.5f));
		}

		void BoxCollider2D::Start()
		{
			using std::unique_ptr;

			for (int i = 0; i < 2; ++i)
			{
				ConvexSide2D* side = new ConvexSide2D(GetTransform(), static_points[i], static_points[i + 1]);
				sides.push_back(unique_ptr<ConvexSideBase>(dynamic_cast<ConvexSideBase*>(side)));
			}

			ConvexSide2D* sideA = new ConvexSide2D(GetTransform(), static_points[3], static_points[2]);
			sides.push_back(unique_ptr<ConvexSideBase>(dynamic_cast<ConvexSideBase*>(sideA)));
			ConvexSide2D* sideB = new ConvexSide2D(GetTransform(), static_points[0], static_points[3]);
			sides.push_back(unique_ptr<ConvexSideBase>(dynamic_cast<ConvexSideBase*>(sideB)));

			this->sqrMaxDstPoint = ConvexCollider2D::GetMaxDstPoints(static_points);
		}
	}
}