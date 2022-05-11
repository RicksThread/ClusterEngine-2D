#include "Player.h"

using namespace ClusterEngine;
using namespace ClusterEngine::Physics;

Player::Player(float speedOnGround, float speedOnAir, float speedJump, Collider2DEventHandler* groundChecker, std::string groundName) :
	speedOnGround(speedOnGround), speedOnAir(speedOnAir), jumpForce(speedJump), groundChecker(groundChecker), groundName(groundName), nGroundedSurface(0), PhysicComponent() {}

void Player::Start()
{
	body = gmObj->GetComponent<PhysicBody2D>();
	groundChecker->OnCollisionEnter.Add(&Player::OnCollisionGroundHitCheck, *this);
	groundChecker->OnCollisionExit.Add(&Player::OnCollisionGroundExitCheck, *this);
	body->interpolation = PhysicBody2D::Interpolation::NONE;
	body->gravity = 9.3f;
}

void Player::Update()
{
	float xInput = 0;
	if (InputsHandler::GetInput(GLFW_KEY_A))
	{
		xInput--;
	}
	if (InputsHandler::GetInput(GLFW_KEY_D)) 
	{
		xInput++;
	}

	float speed = isGrounded() ? speedOnGround : speedOnAir;
	move = Vector2::Normalized(MathUtils::ToVec2(GetTransform()->GetRightDir()) * xInput) * speed;

	if (InputsHandler::GetInputDown(GLFW_KEY_SPACE) && isGrounded())
	{
		body->AddForce(Vector2::Up() * jumpForce, PhysicBody2D::ForceMode2D::CHANGEVELOCITY);
	}

	//hacky trick for a strange behaviour in fixedupdate
}

void Player::FixedUpdate()
{
	body->AddForce(move, PhysicBody2D::ForceMode2D::ACCELERATION);
	HandleDragStates();
}

void Player::OnCollisionGroundHitCheck(Collider2D::CollisionInfo& info)
{
	if (info.colliderB->gmObj->name == groundName) nGroundedSurface++;
}

void Player::OnCollisionGroundExitCheck(Collider2D& colliderA, Collider2D& colliderB)
{
	if (colliderB.gmObj->name == groundName) nGroundedSurface--;
}

bool Player::isGrounded() const
{
	return nGroundedSurface > 0;
}

void Player::HandleDragStates()
{
	if (isGrounded()) body->drag = 7;
	else body->drag = 0.2;
}