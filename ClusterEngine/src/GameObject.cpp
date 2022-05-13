#include "GameObject.h"



namespace ClusterEngine
{
	GameObject::GameObject(const char* name, Transform* transform) : components(0), transform(transform), transformComponent(dynamic_cast<Component*>(transform)), name(name)
	{
		transformComponent->SetGmObj(this);
	}

	void GameObject::AddComponent(Component* component)
	{
		if (component == nullptr) return;

		component->SetGmObj(this);
		components.push_back(std::unique_ptr<Component>(component));
	}

	void GameObject::Start()
	{
		isStarted = true;
		transformComponent->Start();

		for (auto& comp : components)
		{
			comp->Start();
		}
	}

	void GameObject::Update()
	{
		if (!isStarted) return;
		for (auto& comp : components)
		{
			comp->Update();
		}

	}

	void GameObject::DrawUpdate()
	{
		if (!isStarted) return;

		for (auto& comp : components)
		{
			comp->DrawUpdate();
		}
	}

	void GameObject::UpdateTransform()
	{
		if (!isStarted) return;
		transformComponent->Update();
	}

	void GameObject::LateUpdateTransform()
	{
		if (!isStarted) return;
		transformComponent->DrawUpdate();
	}

	void GameObject::Dispose()
	{
		isStarted = false;

		for (auto& comp : components)
		{
			comp.get()->Dispose();
		}
		components.clear();

		if (transform != nullptr)
		{
			delete transform;
		}
	}

	GameObject::~GameObject()
	{
	}

	bool GameObject::hasStarted() 
	{
		return isStarted;
	}

}