#pragma once
#include "SceneBuilder.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include "StandardShaders.h"
#include "Color.h"
#include "Camera.h"
#include "Player.h"
#include "Physics/BoxCollider2D.hpp"
#include "Physics/Collider2DEventHandler.hpp"
#include "Physics/PhysicBody2D.hpp"


class GameSceneBuilder : public ClusterEngine::SceneBuilder
{
public:
	const int ARENA_LENGTH_BLOCKS_LENGTH = 4;
	const int ARENA_LENGTH_BLOCKS_HEIGHT = 5;
	const float BLOCKS_SIZE = 1;

	GameSceneBuilder() = default;
private:
	virtual void Build(ClusterEngine::Scene* scene) override final
	{
		using namespace ClusterEngine::Physics;
		using namespace ClusterEngine;

		ClusterEngine::GameObject* cameraObj = scene->Instantiate("camera", Vector3(0, 0, 0), Quaternion::FromEulerDegree(0, 0, 0), Vector3::One());
		WindowSettings::SetWindowSize(800, 800);

		float arenaLength = (float)ARENA_LENGTH_BLOCKS_LENGTH * BLOCKS_SIZE;
		float arenaHeight = (float)ARENA_LENGTH_BLOCKS_HEIGHT * BLOCKS_SIZE;
		for (int i = 0; i < ARENA_LENGTH_BLOCKS_LENGTH; i++)
		{
			CreateBlock
				("src/images/container.png", 
				 Vector3((float)i* BLOCKS_SIZE -(float)arenaLength *0.5f, -arenaHeight * 0.5f,0),
				Vector3(BLOCKS_SIZE, BLOCKS_SIZE,1), scene
				);
		}

		for (int i = 0; i < ARENA_LENGTH_BLOCKS_HEIGHT; i++)
		{
			CreateBlock
			("src/images/container.png",
				Vector3(-arenaLength*0.5f, (float)i * BLOCKS_SIZE - (float)arenaHeight * 0.5f, 0),
				Vector3(BLOCKS_SIZE, BLOCKS_SIZE, 1), scene
			);
		}

		for (int i = 0; i < ARENA_LENGTH_BLOCKS_LENGTH+1; i++)
		{
			CreateBlock
			("src/images/container.png",
				Vector3((float)i * BLOCKS_SIZE - (float)arenaLength * 0.5f, arenaHeight * 0.5f, 0),
				Vector3(BLOCKS_SIZE, BLOCKS_SIZE, 1), scene
			);
		}

		for (int i = 0; i < ARENA_LENGTH_BLOCKS_HEIGHT; i++)
		{
			CreateBlock
			("src/images/container.png",
				Vector3(arenaLength*0.5f, (float)i * BLOCKS_SIZE - (float)arenaHeight * 0.5f, 0),
				Vector3(BLOCKS_SIZE, BLOCKS_SIZE, 1), scene
			);
		}

		//setup the background

		GameObject* backGround = scene->Instantiate("BackGround", Vector3::Zero(), Vector3(arenaLength, arenaHeight, 1));
		SpriteRenderer* renderer = GetSpriteRenderer("src/images/character.png", Color::White(), 0);
		backGround->AddComponent(renderer);


		//camera setup
		Camera* cam = new Camera(5);
		cameraObj->AddComponent(cam);
	}

	ClusterEngine::SpriteRenderer* GetSpriteRenderer(const char* pathImage, ClusterEngine::Color color, int indexPriority)
	{
		using namespace ClusterEngine;

		ClusterEngine::SpriteRenderer* spriteRenderer = new ClusterEngine::SpriteRenderer(color, indexPriority);
		spriteRenderer->Init();
		Sprite image(pathImage);
		if (pathImage == "src/images/BackGround.jpg")
			std::cout << "n channels: " << image.GetNChannels() << "\n";
		spriteRenderer->SetTexture(image);
		return spriteRenderer;
	}

	ClusterEngine::GameObject* CreateBlock(const char* pathImage,Vector3 pos, Vector3 scale, ClusterEngine::Scene* scene)
	{
		using namespace ClusterEngine;
		using namespace ClusterEngine::Physics;

		GameObject* objBlock = scene->Instantiate("Ground", pos, Quaternion::FromEulerDegree(0,0,0), scale);

		ClusterEngine::SpriteRenderer* spriteRenderer = GetSpriteRenderer(pathImage, Color::White(),1);
		
		BoxCollider2D* boxCollider = new BoxCollider2D(Vector2::One());

		objBlock->AddComponent(spriteRenderer);
		objBlock->AddComponent(boxCollider);
		
		return objBlock;
	}
	
};