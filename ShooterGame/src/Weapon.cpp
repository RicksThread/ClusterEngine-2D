#include "Weapon.h"

using namespace ClusterEngine;

void  Weapon::Update()
{
	//calculate rotation of the weapon
	if (InputsHandler::GetInputMouseDown(GLFW_MOUSE_BUTTON_1))
	{
		Fire();
	}
}

void Weapon::Fire() const
{

	//SceneManager::currentScene->Instantiate();
}