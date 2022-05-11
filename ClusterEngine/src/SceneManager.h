#pragma once
#include <vector>
#include <iostream>
#include <memory>

namespace ClusterEngine
{
	class InitHandler;
	class SceneBuilder;
	class Scene;
	class EngineManager;

	//this class should hold the information about each scene
	class SceneManager
	{
	public:
		static Scene* currentScene;
		static void Init(InitHandler* initHandler);  //handles the initHandler
		static void CreateScene(SceneBuilder* builder);
		static void LoadScene(int index);

	private:
		friend class InitHandler;
		friend class EngineManager;
		static void Update();
		static void RenderUpdate();
		static void Terminate();
		static std::vector<std::unique_ptr<Scene>> scenes;
	};
}