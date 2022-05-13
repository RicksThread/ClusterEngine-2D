#pragma once
#include "InitHandler.h"
#include "GameSceneBuilder.h"

class GameInitialization : public ClusterEngine::InitHandler
{
	virtual void Init(std::vector<std::unique_ptr<ClusterEngine::Scene>>& scenes) override
	{
		//initialize the game
		ClusterEngine::SceneManager::CreateScene(new GameSceneBuilder());
	}
};

