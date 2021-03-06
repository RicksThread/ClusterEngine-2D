#include "Enemy.h"

using namespace ClusterEngine;

Enemy::Enemy(Physics::Collider2DEventHandler* hitsEvent, float gravity)
	: hitsEvent(hitsEvent), gravity(gravity) {}

void Enemy::Start()
{
	hitsEvent->OnCollisionEnter.Add(&Enemy::OnHit, *this);
}

void Enemy::Update()
{
	GetTransform()->position.Y -= EngineTime::GetDeltaTime() * gravity;
}

void Enemy::OnHit(Physics::ConvexCollider2D::CollisionInfo& info)
{
	if (info.colliderB->gmObj->name == "ground" || 
		info.colliderB->gmObj->name == "Player")
	{
		SceneManager::currentScene->Destroy(gmObj);
		if (info.colliderB->gmObj->name == "ground")
		{
			GameManager::Lose();
		}
	}
}

void Enemy::Dispose()
{
	hitsEvent->OnCollisionEnter.Remove(&Enemy::OnHit, *this);
}