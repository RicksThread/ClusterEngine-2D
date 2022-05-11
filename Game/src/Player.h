#pragma once
#include <ClusterEngine.h>

class Player : public ClusterEngine::Physics::PhysicComponent
{
public:
	Player(float speedOnGround, float speedOnAir, float jumpForce, ClusterEngine::Physics::Collider2DEventHandler* groundChecker, std::string groundName);
protected:
	virtual void Start() override;
	virtual void Update() override;

	virtual void FixedUpdate() override;
	~Player() {}
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

