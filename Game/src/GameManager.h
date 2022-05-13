#pragma once
#include <ClusterEngine.h>
#include "Player.h"

class GameManager
{
public:

	static ClusterEngine::MultiCastDelegate<void> OnLost;
	static Player* player;
	static ClusterEngine::Camera* mainCamera;
	static bool isLost;

	static void Lose()
	{
		OnLost.Invoke();
		isLost = true;
	}
};

