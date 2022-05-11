#include "Component.h"

#include "GameObject.h"
#include "Transform.h"

namespace ClusterEngine
{

	Component::Component() : gmObj(nullptr) {}

	void Component::SetGmObj(GameObject* gmObj)
	{
		this->gmObj = gmObj;
	}

	void Component::UnSetGmObj()
	{
		this->gmObj = nullptr;
	}

	Transform* Component::GetTransform()
	{
		return gmObj->transform;
	}

	void Component::Start()
	{}

	void Component::Update()
	{}

	void Component::DrawUpdate()
	{}

	void Component::Dispose()
	{}

	Component::~Component() {}
}