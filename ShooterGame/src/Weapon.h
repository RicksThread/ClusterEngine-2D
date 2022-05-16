#pragma once
#include "Math/Math.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "InputsHandler.h"
#include "SceneManager.h"
#include "Scene.h"

class Weapon : public ClusterEngine::Component
{
	float forcePush;
public:

	Weapon(float forcePush) : forcePush(forcePush) {}

	void virtual Update() override;
	void Fire() const;
	

};


