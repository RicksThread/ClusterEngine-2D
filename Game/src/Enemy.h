#pragma once
#include <ClusterEngine.h>
#include "GameManager.h"

class Enemy : public ClusterEngine::Component
{
public:
	Enemy
		(	
		ClusterEngine::Physics::Collider2DEventHandler* hitsEvent,
		float gravity
		);
protected:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Dispose() override;
private:
	ClusterEngine::Physics::Collider2DEventHandler* hitsEvent;
	float gravity;
	void OnHit(ClusterEngine::Physics::ConvexCollider2D::CollisionInfo& info);
};

