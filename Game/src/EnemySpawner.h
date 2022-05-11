#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Math/Vector2.hpp"
#include "Enemy.h"
#include "EngineTime.hpp"

class EnemySpawner : ClusterEngine::Component
{
public:
	EnemySpawner() = delete;
	EnemySpawner(Vector2 sizeSpawner, float time);

protected:
	virtual void Start() override final;
	virtual void Update() override final;

private:
	
	void SpawnEnemy();
	Vector2 size;
	float timeSpawn;
	float previousTime;
};

