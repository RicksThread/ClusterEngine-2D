#include "EnemySpawner.h"

using namespace ClusterEngine;
using namespace ClusterEngine::Physics;


EnemySpawner::EnemySpawner(Vector2 sizeSpawner, float time)
	: size(sizeSpawner), timeSpawn(time)
{
	std::cout << size << "\n";
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
		SpawnEnemy();
	}
}

void EnemySpawner::SpawnEnemy()
{
	float x = MathUtils::RandomRange(-1.0f, 1.0f) * size.X;
	float y = MathUtils::RandomRange(-1.0f, 1.0f) * size.Y;

	Vector3 enemyPos =
		GetTransform()->position +
		MathUtils::ToVec3(Vector2(
			x * size.X,
			y * size.Y
		));

	GameObject* enemyObj = SceneManager::currentScene->Instantiate("enemy", enemyPos, Vector3::One() * 0.4f);

	BoxCollider2D* boxCollider = new BoxCollider2D(true, Vector2::One());
	Collider2DEventHandler* hitsEvent = new Collider2DEventHandler(boxCollider);
	Enemy* enemy = new Enemy(hitsEvent, 2.6f);
	SpriteRenderer* renderer = new SpriteRenderer(10);
	renderer->SetTexture(*GameSprites::appleSprite.GetTexture());
	enemyObj->AddComponent(boxCollider);
	enemyObj->AddComponent(hitsEvent);
	enemyObj->AddComponent(enemy);
	enemyObj->AddComponent(renderer);
}