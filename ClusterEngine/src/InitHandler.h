#pragma once
#include <vector>
#include <iostream>
#include "Scene.h"

namespace ClusterEngine
{
	class InitHandler
	{
	private:
		friend class SceneManager;
		virtual void Init(std::vector<std::unique_ptr<Scene>>& scenes) = 0;
	};
}