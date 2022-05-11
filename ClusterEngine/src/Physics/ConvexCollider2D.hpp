#pragma once
#include <functional>
#include <memory>
#include <climits>
#include <iterator>
#include "Collider2D.hpp"
#include "../Math/MathUtils.hpp"
#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.hpp"
#include "../GameObject.h"
#include "ConvexShapeInfo.hpp"
#include "ConvexSide2D.hpp"
#include "ProjectionCollider.hpp"

namespace ClusterEngine
{
	namespace Physics
	{

		/**
		 * Collider of a given convex shape
		 */
		class ConvexCollider2D : public Collider2D
		{
		public:
			ConvexCollider2D(bool isTriggerer);

			/**
			 * @param points: Collider's local space vertices
			 */
			ConvexCollider2D(bool isTriggerer, const std::vector<Vector2>& points);

			/**
			 * Returns the world space data of the convex shape
			 */
			ConvexShapeInfo GetConvexColliderWSInfo();

			virtual CollisionInfo Intersect(Collider2D& other) override;
			virtual bool Contains(Vector2 point) override;

			virtual float GetEffectiveRange() const override;

		protected:
			//Collider's local space vertices
			std::vector<Vector2> static_points;

			//Collider's local space sides
			std::vector<std::unique_ptr<ConvexSideBase>> sides;

			float sqrMaxDstPoint;

			float GetMaxDstPoints(const std::vector<Vector2>& points);

			virtual void Update() override {}
			virtual void Start() override;

		};
	}
}