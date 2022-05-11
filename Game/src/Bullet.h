#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Physics/Collider2D.hpp"
#include "Physics/Collider2DEventHandler.hpp"
#include "SceneManager.h"
#include "Scene.h"

class Bullet : public ClusterEngine::Component
{
private:
	ClusterEngine::Physics::Collider2DEventHandler* hitEventsHandler;
	ClusterEngine::Physics::Collider2D* bulletCollider;
	Vector3 move;
	
	void OnHit(ClusterEngine::Physics::Collider2D::CollisionInfo &info);

protected:
	virtual void Update() override;
	virtual void Dispose() override;
public:
	Bullet() = delete;
	Bullet(ClusterEngine::Physics::Collider2DEventHandler* hitEventsHandler, ClusterEngine::Physics::Collider2D* collider);
	void Fire(float acceleration);
	
};