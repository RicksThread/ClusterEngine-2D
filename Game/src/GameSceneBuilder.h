#pragma once
#include <ClusterEngine.h>
#include "Player.h"
#include "Weapon.h"
#include "EnemySpawner.h"
#include "GameSprites.h"

class GameSceneBuilder : public ClusterEngine::SceneBuilder
{
public:
	const int ARENA_LENGTH_BLOCKS_LENGTH = 7;
	const int ARENA_LENGTH_BLOCKS_HEIGHT = 5;
	const float BLOCKS_SIZE = 1.3;

	GameSceneBuilder() = default;
private:
	virtual void Build(ClusterEngine::Scene* scene) override final
	{
		using namespace ClusterEngine::Physics;
		using namespace ClusterEngine;
		Sprite::SetIsFlipped(true);
		GameSprites::GenerateTextures();
		//camera setup
		ClusterEngine::GameObject* cameraObj = scene->Instantiate("camera", Vector3(0, 0, 0), Quaternion::FromEulerDegree(0, 0, 0), Vector3::One());
		Camera* cam = new Camera(7);
		cameraObj->AddComponent(cam);

		WindowSettings::SetWindowSize(800, 800);

		float arenaLength = (float)ARENA_LENGTH_BLOCKS_LENGTH * BLOCKS_SIZE;
		float arenaHeight = (float)ARENA_LENGTH_BLOCKS_HEIGHT * BLOCKS_SIZE;
		for (int i = 0; i < ARENA_LENGTH_BLOCKS_LENGTH; i++)
		{
			CreateBlock
				(*GameSprites::brickSprite.GetTexture(),
					Vector3((float)i * BLOCKS_SIZE - (float)arenaLength * 0.5f, -arenaHeight * 0.5f, 0),
					Vector3(BLOCKS_SIZE, BLOCKS_SIZE, 1), scene
				);
		}

		for (int i = 0; i < ARENA_LENGTH_BLOCKS_HEIGHT; i++)
		{
			CreateBlock
			(*GameSprites::brickSprite.GetTexture(),
				Vector3(-arenaLength * 0.5f, (float)i * BLOCKS_SIZE - (float)arenaHeight * 0.5f, 0),
				Vector3(BLOCKS_SIZE, BLOCKS_SIZE, 1), scene
			);
		}

		for (int i = 0; i < ARENA_LENGTH_BLOCKS_LENGTH + 1; i++)
		{
			CreateBlock
			(*GameSprites::brickSprite.GetTexture(),
				Vector3((float)i * BLOCKS_SIZE - (float)arenaLength * 0.5f, arenaHeight * 0.5f, 0),
				Vector3(BLOCKS_SIZE, BLOCKS_SIZE, 1), scene
			);
		}

		for (int i = 0; i < ARENA_LENGTH_BLOCKS_HEIGHT; i++)
		{
			CreateBlock
			(*GameSprites::brickSprite.GetTexture(),
				Vector3(arenaLength*0.5f, (float)i * BLOCKS_SIZE - (float)arenaHeight * 0.5f, 0),
				Vector3(BLOCKS_SIZE, BLOCKS_SIZE, 1), scene
			);
		}

		//setup the background

		GameObject* backGround = scene->Instantiate("BackGround", Vector3::Zero(), Vector3(arenaLength, arenaHeight, 1));
		SpriteRenderer* renderer = GetSpriteRenderer(*GameSprites::BackGroundSprite.GetTexture(), Color::White(), 0);
		backGround->AddComponent(renderer);



		GameObject* playerObj = scene->Instantiate("Player", Vector3::Zero());
		SpriteRenderer* playerRenderer = GetSpriteRenderer(*GameSprites::playerSprite.GetTexture(), Color::White(), 3);
		playerObj->AddComponent(playerRenderer);

		GameObject* groundChecker = scene->Instantiate("GroundChecker", Vector3(0, -0.5f, 0));
		BoxCollider2D* groundCollider = new BoxCollider2D(Vector2(0.8f,0.2f));
		groundCollider->isTriggerer = true;
		Collider2DEventHandler* groundCheckEventHandler = new Collider2DEventHandler(groundCollider);
		groundChecker->AddComponent(groundCollider);
		groundChecker->AddComponent(groundCheckEventHandler);
		
		groundChecker->transform->SetParent(playerObj->transform);
		BoxCollider2D* boxCollider = new BoxCollider2D(Vector2::One());
		PhysicBody2D* playerBody = new PhysicBody2D(boxCollider, 3, 3);
		Player* player = new Player(30, 2, 7, groundCheckEventHandler, "ground");
		playerObj->AddComponent(player);
		playerObj->AddComponent(boxCollider);
		playerObj->AddComponent(playerBody); 

		GameObject* weaponObj = scene->Instantiate("Weapon", Vector3(0,-0.1,0), Vector3(1,0.5,1));
		Weapon* weapon = new Weapon(cam, 10);
		weaponObj->AddComponent(weapon);
		SpriteRenderer* weaponRenderer = GetSpriteRenderer(*GameSprites::ShotgunSprite.GetTexture(), Color::White(), 4);
		weaponObj->AddComponent(weaponRenderer);

		weaponObj->transform->SetParent(playerObj->transform); 

		GameObject* spawnerObj = scene->Instantiate("Spawner", Vector3(0, (float)arenaHeight * 0.3f, -1));
		EnemySpawner* spawner = new EnemySpawner(Vector2(arenaLength*0.2f, arenaHeight *0.1f), 1);
		spawnerObj->AddComponent(spawner);
	}

	ClusterEngine::SpriteRenderer* GetSpriteRenderer(TEXTURE& tex, ClusterEngine::Color color, int indexPriority)
	{
		using namespace ClusterEngine;

		ClusterEngine::SpriteRenderer* spriteRenderer = new ClusterEngine::SpriteRenderer(color, indexPriority);

		spriteRenderer->SetTexture(tex);
		return spriteRenderer;
	}

	ClusterEngine::GameObject* CreateBlock(TEXTURE& tex, Vector3 pos, Vector3 scale, ClusterEngine::Scene* scene)
	{
		using namespace ClusterEngine;
		using namespace ClusterEngine::Physics;

		GameObject* objBlock = scene->Instantiate("ground", pos, Quaternion::FromEulerDegree(0,0,0), scale);

		ClusterEngine::SpriteRenderer* spriteRenderer = GetSpriteRenderer(tex, Color::White(),1);
		
		BoxCollider2D* boxCollider = new BoxCollider2D(Vector2::One());

		objBlock->AddComponent(spriteRenderer);
		objBlock->AddComponent(boxCollider);
		
		return objBlock;
	}
	
};