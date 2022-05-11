#include "EnemySpawner.h"

using namespace ClusterEngine;
using namespace ClusterEngine::Physics;


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
	std::cout << EngineTime::GetTime() << "\n";
	if ((EngineTime::GetTime() - previousTime) >= timeSpawn)
	{
		previousTime = EngineTime::GetTime();
		SpawnEnemy();
		std::cout << "spawn\n";
	}
}

void EnemySpawner::SpawnEnemy()
{
	Vector3 enemyPos =
		GetTransform()->position +
		MathUtils::ToVec3(Vector2(
			MathUtils::RandomRange(-1.0f, 1.0f) * size.X,
			MathUtils::RandomRange(-1.0f, 1.0f) * size.Y
		));
	GameObject* enemyObj = SceneManager::currentScene->Instantiate("enemy", enemyPos, Vector3::One() * 0.4f);

	BoxCollider2D* boxCollider = new BoxCollider2D(true, Vector2::One());
	Collider2DEventHandler* hitsEvent = new Collider2DEventHandler(boxCollider);
	Enemy* enemy = new Enemy(hitsEvent, 10);
	SpriteRenderer* renderer = new SpriteRenderer(10);

	enemyObj->AddComponent(boxCollider);
	enemyObj->AddComponent(hitsEvent);
	enemyObj->AddComponent(enemy);
	enemyObj->AddComponent(renderer);
}