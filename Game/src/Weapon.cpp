#include "Weapon.h"

using namespace ClusterEngine;
using namespace ClusterEngine::Physics;

void  Weapon::Update()
{
	//calculate rotation of the weapon
	Vector2 directionPointing = camera->GetMousePosWorldSpace() - MathUtils::ToVec2(gmObj->transform->position);
	Vector3 upWardDir = Quaternion::FromEulerDegree(0, 0, 90) * MathUtils::ToVec3(Vector2::Normalized(directionPointing));
	Quaternion rotation = Quaternion::LookRotation(Vector3::Backward(), -Vector3::Normalized(upWardDir));
	gmObj->transform->rotation = rotation;

	if (InputsHandler::GetInputMouseDown(GLFW_MOUSE_BUTTON_1))
	{
		Fire();
	}
}

void Weapon::Fire()
{
	GameObject* bullet = SceneManager::currentScene->Instantiate("bullet", GetTransform()->position, GetTransform()->rotation);
	
	//set the bullet renderer
	SpriteRenderer* bulletRenderer = new SpriteRenderer(6);
	Sprite bulletSprite("src/images/bullet.png");
	bulletRenderer->SetTexture(bulletSprite);
	bullet->AddComponent(bulletRenderer);

	BoxCollider2D* bulletBoxCollider = new BoxCollider2D(Vector2::One());
	Collider2DEventHandler* bulletHitHandler = new Collider2DEventHandler(bulletBoxCollider);

	Bullet* bulletComp = new Bullet(bulletHitHandler, bulletBoxCollider);

	bullet->AddComponent(bulletBoxCollider);
	bullet->AddComponent(bulletHitHandler);
	bullet->AddComponent(bulletComp);
	bullet->transform->scale = Vector3::One() * 0.45f;
	bulletComp->Fire(forcePush);
}