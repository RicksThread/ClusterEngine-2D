#include "GameSprites.h"

ClusterEngine::Sprite GameSprites::appleSprite;
ClusterEngine::Sprite GameSprites::brickSprite;
ClusterEngine::Sprite GameSprites::playerSprite;
ClusterEngine::Sprite GameSprites::bulletSprite;
ClusterEngine::Sprite GameSprites::ShotgunSprite;
ClusterEngine::Sprite GameSprites::BackGroundSprite;

void GameSprites::GenerateTextures()
{
	appleSprite.SetPath("src/images/apple.png");
	brickSprite.SetPath("src/images/brick.jpg");
	playerSprite.SetPath("src/images/character.png");
	bulletSprite.SetPath("src/images/bullet.png");
	ShotgunSprite.SetPath("src/images/Shotgun.png");
	BackGroundSprite.SetPath("src/images/BackGround.jpg");

	appleSprite.CreateTexture();
	brickSprite.CreateTexture();
	playerSprite.CreateTexture();
	bulletSprite.CreateTexture();
	ShotgunSprite.CreateTexture();
	BackGroundSprite.CreateTexture();
}d