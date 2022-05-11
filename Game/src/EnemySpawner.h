#pragma once
#include <ClusterEngine.h>
#include "Enemy.h"

class EnemySpawner : public ClusterEngine::Component
{
public:
	EnemySpawner() = delete;
	EnemySpawner(Vector2 sizeSpawner, float time);

protected:
	virtual void Start() override final;
	virtual void Update() override final;

private:
	Vector2 size;
	Sprite enemySprite;
	float timeSpawn;
	float previousTime;
	
	void SpawnEnemy();
};