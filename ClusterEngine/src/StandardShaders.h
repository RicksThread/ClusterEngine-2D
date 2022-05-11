#pragma once
#include "Shader.h"

namespace ClusterEngine
{
	class EngineManager;

	class StandardShaders
	{
	public:
		static ClusterEngine::Shader simpleShader;

	private:
		friend class EngineManager;

		static void Initialize();
	};

}
