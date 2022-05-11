#include "Scene.h"

#include "SceneBuilder.h"

namespace ClusterEngine
{
	Scene::Scene() : gameobjects(0), newGameobjects(0), builder(nullptr), isBuilded(false) {}

	Scene::Scene(SceneBuilder* builder) : gameobjects(0), newGameobjects(0), builder(builder), isBuilded(false)
	{}

	GameObject* Scene::Instantiate(const char* name, const Vector3& position, const Quaternion& rotation, const Vector3& scale)
	{
		Transform* transform = new Transform(position, rotation, scale);

		GameObject* GmObj = new GameObject(name, transform);
		newGameobjects.push_back(GmObj);
		return GmObj;
	}

	GameObject* Scene::Instantiate(const char* name, const Vector3& position, const Quaternion& rotation)
	{
		return Instantiate(name, position, rotation, Vector3::One());
	}

	GameObject* Scene::Instantiate(const char* name, const Vector3& position, const Vector3& scale)
	{
		return Instantiate(name, position, Quaternion::Identity(), scale);
	}

	GameObject* Scene::Instantiate(const char* name, const Vector3& position)
	{
		return Instantiate(name, position, Quaternion::Identity(), Vector3::One());
	}

	void Scene::Destroy(GameObject* gmObj)
	{
		if (deleteGameobjects.count(gmObj)) return;
		deleteGameobjects.insert(gmObj);
		for (int i = 0; i < gmObj->transform->GetChildCount(); ++i)
		{
			Destroy(gmObj->transform->GetChild(i)->gmObj);
		}
	}

	void Scene::Start()
	{
		if (isBuilded) return;

		isBuilded = true;
		Scene* scene = this;

		builder->Build(scene);

		for (auto& gmObjs : gameobjects)
		{
			gmObjs->Start();
		}

	}

	void Scene::Update()
	{
		for (auto& gmObjs : gameobjects)
		{
			gmObjs->UpdateTransform();
		}
		for (auto& gmObjs : gameobjects)
		{
			gmObjs->Update();
		}
	}

	void Scene::RenderUpdate()
	{
		for (auto& gmObjs : gameobjects)
		{
			gmObjs->LateUpdateTransform();
		}

		for (auto& gmObjs : gameobjects)
		{
			gmObjs->DrawUpdate();
		}
	}

	void Scene::DestroyUpdate()
	{
		if (newGameobjects.size() > 0)
		{
			for (auto& newGmObjs : newGameobjects)
			{
				gameobjects.push_back(std::unique_ptr<GameObject>(newGmObjs));
				newGmObjs->Start();
			}
			newGameobjects.clear();
		}

		if (deleteGameobjects.size() > 0)
		{
			std::vector<int> destroyedObjsIndex(deleteGameobjects.size());
			int i = 0;

			for (auto& delObjs : deleteGameobjects)
			{
				//get the iterator position from the given gmObj
				auto isSameGmObject = [&](auto gmObjptr) { return gmObjptr. == delObjs;  };
				auto it = std::find_if(gameobjects.begin(), gameobjects.end(), [&](std::unique_ptr<GameObject>& gmObjptr) { return gmObjptr.get() == delObjs;  });
				
				int index = std::distance(gameobjects.begin(), it);
				destroyedObjsIndex[i] = index;
				
				//call its destroy
				gameobjects[index].get()->Dispose();
				
				i++;
			}
			deleteGameobjects.clear();

			int biggestNDestroyed = 0;
			for (int i = 0; i < destroyedObjsIndex.size(); i++)
			{
				if (destroyedObjsIndex[i] < biggestNDestroyed)
				std::cout << "destroy at: " << destroyedObjsIndex[i] << "vector size: " << gameobjects.size() << "\n";
				//remove it from the vector and release it from memory
				gameobjects.erase(gameobjects.begin() + destroyedObjsIndex[i]);
				std::cout << "aqs dhusa d\n";
			}
		}

	}

	void Scene::Destroy()
	{
		for (auto& gmObjs : gameobjects)
		{
			gmObjs.release();
		}

		isBuilded = false;
		gameobjects.clear();
	}
}