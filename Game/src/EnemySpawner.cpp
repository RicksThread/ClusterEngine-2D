#include "EnemySpawner.h"

using namespace ClusterEngine;


EnemySpawner::EnemySpawner(Vector2 sizeSpawner, float time)
	: size(size), timeSpawn(time)
{
}

void EnemySpawner::Start()
{
	previousTime = EngineTime::GetTime();
}

void EnemySpawner::Update()
{
	if ((EngineTime::GetTime() - previousTime) >= timeSpawn)
	{
		previousTime = EngineTime::GetTime();

	}
}

void EnemySpawner::SpawnEnemy()
{
	
}