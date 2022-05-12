#pragma once
#include <vector>
#include <iostream>
#include "SceneManager.h"
#include "GameObject.h"
#include <unordered_set>
namespace ClusterEngine
{
	class SceneBuilder;

	//Holds gameobjects are manages their action timing
	class Scene
	{
	public:
		Scene() = delete;

		//remove copy and move operations
		Scene(const Scene&) = delete;
		Scene(Scene&&) = delete;
		Scene& operator=(const Scene&) = delete;
		Scene& operator=(Scene&&) = delete;

		Scene(SceneBuilder* sceneBuilder);
		GameObject* Instantiate(const char* name, const Vector3& position, const Quaternion& rotation, const Vector3& scale);
		GameObject* Instantiate(const char* name, const Vector3& position, const Quaternion& rotation);
		GameObject* Instantiate(const char* name, const Vector3& position, const Vector3& scale);
		GameObject* Instantiate(const char* name, const Vector3& position);
		
		/**
		* Release the gameobject from the scene and memory
		**/
		void Destroy(GameObject* gmObj);
	private:
		std::unique_ptr<SceneBuilder> builder;
		bool isBuilded;

		//builds the scene and starts the gameobjects
		void Start();

		//updates the scene
		void Update();

		//updates the draw callbacks
		void RenderUpdate();

		//iterate through all the destroyed gameobjects to free them in the scene
		void DestroyUpdate();

		//finalize the scene and dispose the memory
		void Destroy();

		std::vector<GameObject*> newGameobjects;
		std::unordered_set<GameObject*> deleteGameobjects;
		std::vector<std::unique_ptr<GameObject>> gameobjects;
		friend class SceneManager;
	};
}