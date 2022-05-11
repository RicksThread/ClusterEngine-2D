#pragma once
#include <type_traits>
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <iostream>
#include "Transform.h"
#include "Component.h"

namespace ClusterEngine
{
	class Scene;

	class GameObject
	{
	public:

		/**
 		* name of the gameobject
 		*/ 
		std::string name;

		/**
 		* coordinates, rotation and scale of the current gameobject
 		*/ 
		Transform* transform;

		GameObject(const char* name, Transform* transform);

		/**
		*  Adds a component to the Gameobject and set it up
 		*/ 
		void AddComponent(Component* component);

		/**
		* Retrieves the given type of component from the gameobject
		* @tparam T: Component's type
		* @return: Component's pointer with its type
		*/ 
		template<class T>
		T* GetComponent();

		/**
		* Removes the first type of component of that given type
		* @tparam T: Component's type
		*/ 
		template<class T>
		void RemoveComponent();

		bool hasStarted();
		
		~GameObject();
	private:
		friend class Scene;

		bool isStarted = false;
		std::vector<std::unique_ptr<Component>> components;
		Component* transformComponent;

		void Start();
	
		void UpdateTransform();
		void Update();

		void LateUpdateTransform();
		void DrawUpdate();

		void Dispose();
	};

	template<class T>
	void GameObject::RemoveComponent()
	{
		if (!std::is_base_of<Component, T>())
		{
			std::cout << "the type is not a component!\n";
			return;
		}

		int i = 0;
		bool isRemoved = false;
		for (auto it = components.begin(); it != components.end(); ++it, ++i)
		{
			if (dynamic_cast<T*>(components[i].get()))
			{
				isRemoved = true;
				components[i]->UnSetGmObj();
				components.erase(it);
				break;
			}
		}

		if (!isRemoved)
		{
			std::cout << "Component NOT FOUND!\n";
		}
	}

	template<class T>
	T* GameObject::GetComponent()
	{
		if (!std::is_base_of<Component, T>()) 
		{
			std::cout << "the type is not a component!\n";
			return nullptr;
		}

		for (int i = 0; i < components.size(); ++i)
		{
			if (dynamic_cast<T*>(components[i].get()))
			{
				return dynamic_cast<T*>(components[i].get());
			}
		}

		//std::cout << "Component NOT FOUND!\n";
		return nullptr;
	}

}