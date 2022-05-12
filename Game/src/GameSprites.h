#pragma once
#include <ClusterEngine.h>

struct GameSprites
{
	static ClusterEngine::Sprite appleSprite;
	static ClusterEngine::Sprite brickSprite;
	static ClusterEngine::Sprite playerSprite;
	static ClusterEngine::Sprite bulletSprite;
	static ClusterEngine::Sprite ShotgunSprite;
	static ClusterEngine::Sprite BackGroundSprite;

	static void GenerateTextures();
};