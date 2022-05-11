#include "SceneManager.h"

#include "SceneBuilder.h"
#include "Scene.h"
#include "InitHandler.h"


namespace ClusterEngine
{
	std::vector<std::unique_ptr<Scene>> SceneManager::scenes(0);
	Scene* SceneManager::currentScene;

	void SceneManager::CreateScene(SceneBuilder* builder)
	{
		Scene* a = new Scene(builder);
		scenes.push_back(std::move(std::unique_ptr<Scene>(a)));
	}

	void SceneManager::LoadScene(int index)
	{

		if (index >= scenes.size())
		{
			return;
		}

		if (currentScene != nullptr)
			currentScene->Destroy();
		currentScene = scenes[index].get();
		currentScene->Start();

	}

	void SceneManager::Init(InitHandler* initHandler)
	{
		initHandler->Init(scenes);
	}

	void SceneManager::Terminate()
	{
		for (int i = 0; i < scenes.size(); i++)
		{
			scenes[i].get()->Destroy();
			scenes[i].release();
		}
		scenes.clear();
	}

	void SceneManager::Update()
	{
		if (currentScene != nullptr)
			currentScene->Update();
	}

	void SceneManager::RenderUpdate()
	{
		if (currentScene != nullptr)
			currentScene->RenderUpdate();

		currentScene->DestroyUpdate();
	}
}