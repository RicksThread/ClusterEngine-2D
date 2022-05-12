#pragma once
#include <iostream>
#include <glad/glad.h>
#include "Math/Math.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Color.h"
#include "Sprite.hpp"
#include "Component.h"
#include "GraphicsConventions.h"


namespace ClusterEngine
{

	class SpriteRenderer : public Component
	{
	public:
		using Base = Component;

		enum class VAOType { SQUARE };

		VAOType thisVao;
		Color color;

		SpriteRenderer();

		//remove copy and move operations
		SpriteRenderer(const SpriteRenderer&) = delete;
		SpriteRenderer(SpriteRenderer&&) = delete;
		SpriteRenderer& operator=(const SpriteRenderer&) = delete;
		SpriteRenderer& operator=(SpriteRenderer&&) = delete;

		//declare allowed constructors
		SpriteRenderer(int priorityIndex);
		SpriteRenderer(Color color, int priorityIndex);
		SpriteRenderer(VAOType typeVAO, Color color, int priorityIndex);

		void Draw();
		void SetTexture(unsigned int& tex);

		inline int GetPriorityIndex() const noexcept;
		void SetPriorityIndex(int index);

	protected:
		void virtual Start() override;
		void virtual DrawUpdate() override;
		void virtual Dispose() override;
	private:
		SHADER_ID transformID, rotationID, scaleID, colorID, textureID;
		TEXTURE texture;
		unsigned int priorityIndex;
		Shader* shader;

		//it offsets the priority based on how many sprites are in the scene
		static int priorityOffSet;
		static VAO_DATA square;
		static bool globalsInitialized;

		//initialize the vao and id settings
		void Init();
		VAO_DATA GetDataVAO(VAOType type);
	};
};

