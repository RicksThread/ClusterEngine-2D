#pragma once
#include <ClusterEngine.h>
#include "Bullet.h"

class Weapon : public ClusterEngine::Component
{
	float forcePush;
	ClusterEngine::Camera* camera;
public:

	Weapon(ClusterEngine::Camera* camera, float forcePush) : forcePush(forcePush), camera(camera) {}

	void virtual Update() override;
	void Fire();
};


