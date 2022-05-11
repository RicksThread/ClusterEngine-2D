#pragma once
#include "PhysicBody2D.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		PhysicBody2D::PhysicBody2D(Collider2D* collider, float mass, float drag)
			:	mass(mass), drag(drag), bodiesCollided(0),
				velocity(Vector2::Zero()), Collider2DEventHandler(collider) 
		{}

		void PhysicBody2D::Start()
		{
			Collider2DEventHandler::Start();
			OnCollisionEnter.Add(&PhysicBody2D::CollisionPhysic, *this);
			OnCollisionStay.Add(&PhysicBody2D::CollisionPhysic, *this);
		}

		void PhysicBody2D::Update()
		{
			if (interpolation == Interpolation::INTERPOLATE)
				GetTransform()->position += MathUtils::ToVec3(velocity) * EngineTime::GetDeltaTime();
		}

		void PhysicBody2D::FixedUpdate()
		{
			if (bodiesCollided.size() > 0) bodiesCollided.clear();

			if (Vector2::SqrMagnitude(velocity) < 0.00001f)
				velocity = Vector2::Zero();


			if (interpolation == Interpolation::NONE)
				GetTransform()->position += MathUtils::ToVec3(velocity) * PhysicsManager::GetFixedDeltaTime();

			HandleDrag();
			HandleGravity();

			Collider2DEventHandler::FixedUpdate();
		}

		void PhysicBody2D::AddForce(Vector2 offSet, ForceMode2D forceMode)
		{
			switch (forceMode)
			{
			case ForceMode2D::FORCE:
				velocity += offSet / mass * PhysicsManager::GetFixedDeltaTime();
				break;

			case ForceMode2D::IMPULSE:
				velocity += offSet / mass;
				break;
			case ForceMode2D::ACCELERATION:
				velocity += offSet * PhysicsManager::GetFixedDeltaTime();
				break;
			case ForceMode2D::CHANGEVELOCITY:
				velocity += offSet;
				break;
			}
		}

		inline Vector2 PhysicBody2D::GetVelocity() const
		{
			return velocity;
		}

		void PhysicBody2D::CollisionPhysic(Collider2D::CollisionInfo& info)
		{
			if (info.colliderB->isTriggerer) return;


			PhysicBody2D* otherBody = info.colliderB->gmObj->GetComponent<PhysicBody2D>();

			if (bodiesCollided.count(otherBody)) return;

			gmObj->transform->position += MathUtils::ToVec3(info.collisionNormal) * info.deltaError;

			//velocity of impact
			float directHitVelocity = Vector2::Dot(info.collisionNormal, Vector2::Normalized(velocity)) * Vector2::Magnitude(velocity);


			if (otherBody != nullptr)
			{
				//the velocity that experienced the other collider on collision
				float directHitVelocityOther = Vector2::Dot(info.collisionNormal, Vector2::Normalized(otherBody->velocity)) * Vector2::Magnitude(otherBody->velocity);

				float velocityOther = (2 * mass * directHitVelocity + otherBody->mass * directHitVelocityOther - mass * directHitVelocityOther) / (mass + otherBody->mass);
				float velocity = ((2 * otherBody->mass * directHitVelocityOther) + (mass * directHitVelocity) - (otherBody->mass * directHitVelocity)) / (mass + otherBody->mass);

				AddForce(info.collisionNormal * (velocity - directHitVelocity), ForceMode2D::CHANGEVELOCITY);
				otherBody->AddForce(info.collisionNormal * (velocityOther - directHitVelocityOther), ForceMode2D::CHANGEVELOCITY);

				otherBody->bodiesCollided.insert(this);
			}
			else
			{
				Vector2 forceCollision = -directHitVelocity * info.collisionNormal * mass;
				AddForce(forceCollision, ForceMode2D::IMPULSE);
			}
		}

		void PhysicBody2D::HandleDrag()
		{
			velocity *= 1 - (drag * PhysicsManager::GetFixedDeltaTime());
		}

		void PhysicBody2D::HandleGravity()
		{
			AddForce(Vector2::Down() * gravity, ForceMode2D::ACCELERATION);
		}
	}
}