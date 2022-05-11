#include "Collider2DEventHandler.hpp"

namespace ClusterEngine
{
	namespace Physics
	{

		Collider2DEventHandler::Collider2DEventHandler(Collider2D* collider) :
			currentCollider(collider),
			collidersCollisionOnExitQueue(0),
			collisionInfoCollisionOnEnter(0),
			collisionInfoCollisionOnStay(0)

		{
			collidersCollidingPrevious = std::unique_ptr<std::unordered_set<Collider2D*>>(new std::unordered_set<Collider2D*>(0));
		}

		void Collider2DEventHandler::Start()
		{
			std::cout << "object started: " << gmObj->name << "\n";
		}

		void Collider2DEventHandler::FixedUpdate()
		{
			using std::cout;
			
			collidersColliding = std::unique_ptr<std::unordered_set<Collider2D*>>(new std::unordered_set<Collider2D*>(0));

			for (const auto& collider : Collider2D::colliders)
			{
				//the current collider can't collider with itself
				if (currentCollider == collider) continue;
				
				bool wasContained = collidersCollidingPrevious->count(collider);

				//calculate if the distance between this and the other collider 
				//is less than the effective range of the other plus this

				float sqrDstToOther = Vector2::Magnitude(MathUtils::ToVec2(GetTransform()->position) - MathUtils::ToVec2(collider->GetTransform()->position));
				float tEffectiveRange = (collider->GetEffectiveRange() + currentCollider->GetEffectiveRange()) * 1.04f;

				if (sqrDstToOther < tEffectiveRange)
				{
					Collider2D::CollisionInfo info = currentCollider->Intersect(*collider);

					if (info.isColliding)
					{
						if (!collidersCollidingPrevious->count(info.colliderB))
						{
							//the collider has just collided in this iteration
							collisionInfoCollisionOnEnter.push_back(info);
						}
						else
						{
							//if the collider was already present
							collisionInfoCollisionOnStay.push_back(info);
						}

						collidersColliding->insert(collider);
					}
					else if (wasContained)
					{
						//was colliding 
						collidersCollisionOnExitQueue.push_back(collider);
					}

				}
				else if (wasContained)
				{
					//it is sure that the collider is not colliding anymore
					collidersCollisionOnExitQueue.push_back(collider);
				}
			}

			//push down the content of the current to the previous for the next iteration
			collidersCollidingPrevious.release();
			collidersCollidingPrevious = std::move(collidersColliding);
		}

		void Collider2DEventHandler::CollisionUpdate()
		{
			if (collisionInfoCollisionOnEnter.size() > 0)
			{
				for (auto& onEnterQueueElement : collisionInfoCollisionOnEnter)
					OnCollisionEnter.Invoke(onEnterQueueElement);
				collisionInfoCollisionOnEnter.clear();
			}
			if (collisionInfoCollisionOnStay.size() > 0)
			{
				for (auto& onStayQueueElement : collisionInfoCollisionOnStay)
					OnCollisionStay.Invoke(onStayQueueElement);
				collisionInfoCollisionOnStay.clear();
			}
			if (collidersCollisionOnExitQueue.size() > 0)
			{
				for (auto& onExitQueueElement : collidersCollisionOnExitQueue)
					OnCollisionExit.Invoke(*currentCollider, *onExitQueueElement);
				collidersCollisionOnExitQueue.clear();
			}
		}

	}
}