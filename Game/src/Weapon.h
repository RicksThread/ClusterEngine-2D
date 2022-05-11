#pragma once
#include "Math/Math.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "InputsHandler.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Math/MathUtils.hpp"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "Bullet.h"
#include "Physics/BoxCollider2D.hpp"
#include "Physics/Collider2DEventHandler.hpp"

class Weapon : public ClusterEngine::Component
{
	float forcePush;
	ClusterEngine::Camera* camera;
public:

	Weapon(ClusterEngine::Camera* camera, float forcePush) : forcePush(forcePush), camera(camera) {}

	void virtual Update() override;
	void Fire();
};


