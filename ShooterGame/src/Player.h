#pragma once
#include <string>
#include "Component.h"
#include "InputsHandler.h"
#include "Math/Vector3.hpp"
#include "Time.h"
#include "GameObject.h"
#include "Physics/PhysicBody2D.hpp"

class Player : public ClusterEngine::Physics::PhysicComponent
{
public:
	Player(float speedOnGround, float speedOnAir, float jumpForce, ClusterEngine::Physics::Collider2DEventHandler* groundChecker, std::string groundName);
protected:
	virtual void Start() override;
	virtual void Update() override;

	virtual void FixedUpdate() override;
	virtual void PhysicDispose() override;
private:
	ClusterEngine::Physics::PhysicBody2D* body;
	
	ClusterEngine::Physics::Collider2DEventHandler* groundChecker;
	std::string groundName;

	Vector2 move;
	float speedOnGround;
	float speedOnAir;

	float jumpForce;
	int nGroundedSurface;

	void OnCollisionGroundHitCheck(ClusterEngine::Physics::Collider2D::CollisionInfo& info);
	void OnCollisionGroundExitCheck(ClusterEngine::Physics::Collider2D& colliderA, ClusterEngine::Physics::Collider2D& colliderB);

	bool isGrounded() const;
	void HandleDragStates();

};

