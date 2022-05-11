#pragma once
#include "Scene.h"

namespace ClusterEngine
{
	//class which should build scenes
	class SceneBuilder
	{

	private:
		friend class Scene;

		virtual void Build(Scene* scene) = 0;
	};
}
