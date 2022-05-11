#include "StandardShaders.h"

namespace ClusterEngine
{
	ClusterEngine::Shader StandardShaders::simpleShader;

	void StandardShaders::Initialize()
	{
		ClusterEngine::Shader shader("src/shaders/simpleVertex.shader", "src/shaders/simpleFragment.shader");
		std::cout << "scoc\n ";
		shader.Use();
		std::cout << "tromboc\n";
		simpleShader = shader;
	}
}