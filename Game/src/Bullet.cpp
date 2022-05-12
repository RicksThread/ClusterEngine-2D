#include "Bullet.h"

using namespace ClusterEngine;
using namespace ClusterEngine::Physics;

Bullet::Bullet(Collider2DEventHandler* hitEventsHandler, Collider2D* collider) : hitEventsHandler(hitEventsHandler), bulletCollider(collider)
{
	bulletCollider->isTriggerer = true;
	hitEventsHandler->OnCollisionEnter.Add(&Bullet::OnHit, *this);
}

void Bullet::OnHit(Collider2D::CollisionInfo& info)
{
	if (info.colliderB->gmObj->name == "ground") 
		SceneManager::currentScene->Destroy(this->gmObj);
	if (info.colliderB->gmObj->name == "enemy")
	{
		SceneManager::currentScene->Destroy(info.colliderB->gmObj);
		SceneManager::currentScene->Destroy(this->gmObj);
	}
}

void Bullet::Update()
{
	gmObj->transform->position += move * EngineTime::GetDeltaTime();
}

void Bullet::Fire(float acceleration)
{
	move = GetTransform()->GetRightDir() * acceleration;
}

void Bullet::Dispose()
{
	hitEventsHandler->OnCollisionEnter.Remove(&Bullet::OnHit, *this);
}