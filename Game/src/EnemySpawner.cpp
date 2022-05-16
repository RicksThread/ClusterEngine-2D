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
	velocityDrop = 1;
	previousTime = EngineTime::GetTime();
}

void EnemySpawner::Update()
{
	if (timeSpawn > 0.5) timeSpawn -= EngineTime::GetDeltaTime() * 0.1f;
	if ((EngineTime::GetTime() - previousTime) >= timeSpawn)
	{
		if (velocityDrop <= 14)
			velocityDrop += 0.01f;
		previousTime = EngineTime::GetTime();
		SpawnEnemy();
	}
}

void EnemySpawner::SpawnEnemy()
{
	float x = MathUtils::RandomRange(-1.0f, 1.0f) * size.X * 0.7;
	float y = MathUtils::RandomRange(-1.0f, 1.0f) * size.Y * 0.4f;

	Vector3 enemyPos =
		GetTransform()->position +
		MathUtils::ToVec3(Vector2(
			x * size.X,
			y * size.Y
		));

	GameObject* enemyObj = SceneManager::currentScene->Instantiate("enemy", enemyPos, Vector3::One() * 0.6);

	BoxCollider2D* boxCollider = new BoxCollider2D(true, Vector2::One());
	Collider2DEventHandler* hitsEvent = new Collider2DEventHandler(boxCollider);
	Enemy* enemy = new Enemy(hitsEvent, velocityDrop);
	SpriteRenderer* renderer = new SpriteRenderer(10);
	renderer->SetTexture(*GameSprites::appleSprite.GetTexture());
	enemyObj->AddComponent(boxCollider);
	enemyObj->AddComponent(hitsEvent);
	enemyObj->AddComponent(enemy);
	enemyObj->AddComponent(renderer);
}