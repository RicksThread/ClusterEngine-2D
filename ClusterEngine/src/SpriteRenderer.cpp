#include "SpriteRenderer.h"
#include "GameObject.h"
#include "StandardShaders.h"
#include "Math/MathUtils.hpp"
#include <iostream>


namespace ClusterEngine
{
	VAO_DATA SpriteRenderer::square;
	bool SpriteRenderer::globalsInitialized = false;
	int SpriteRenderer::priorityOffSet = 0;
	SpriteRenderer::SpriteRenderer() : thisVao(VAOType::SQUARE), color(Color::White()), priorityIndex(0), Component()
	{
		Init();
	}

	SpriteRenderer::SpriteRenderer(int priorityIndex)
		: thisVao(VAOType::SQUARE), color(Color::White()), priorityIndex(priorityIndex), Component()
	{
		Init();
	}

	SpriteRenderer::SpriteRenderer(Color color, int priorityIndex)
		: thisVao(VAOType::SQUARE), color(color), priorityIndex(priorityIndex), Component()
	{
		Init();
	}

	SpriteRenderer::SpriteRenderer(VAOType vaoType, Color color, int priorityIndex) : thisVao(vaoType), color(color), priorityIndex(priorityIndex), Component()
	{
		Init();
	}



	void SpriteRenderer::Init()
	{

		shader = &StandardShaders::simpleShader;

		transformID = glGetUniformLocation(shader->ID, "transform");
		scaleID = glGetUniformLocation(shader->ID, "scale");
		rotationID = glGetUniformLocation(shader->ID, "rotation");
		colorID = glGetUniformLocation(shader->ID, "color");
		textureID = glGetUniformLocation(shader->ID, "texture0");

		if (globalsInitialized) return;
		float vertices[] = {
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 3, 2
		};

		unsigned int VBO, EBO;

		//vertex buffer object
		glGenBuffers(1, &VBO);

		//element buffer object
		glGenBuffers(1, &EBO);

		//VAO
		glGenVertexArrays(1, &square);
		//bind VAO temporarily to store calls
		glBindVertexArray(square);

		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//telling opengl how to interpret vertex attributes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		globalsInitialized = true;
	}

	void SpriteRenderer::Draw()
	{
		Vector3 position = GetTransform()->position;
		Vector3 rotationEuler = Quaternion::ToEulerDegree(GetTransform()->rotation);
		Vector3 size = GetTransform()->scale;

		shader->Use();

		//TO DO: improve the system by lowering the set uniform calls
		//wrap every information in a struct and send it once

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(position.X, position.Y, position.Z));
		glm::mat4 scale = glm::mat4(1.0f);
		scale = glm::scale(scale, glm::vec3(size.X, size.Y, size.Z));

		glm::mat4 rotation = glm::mat4(1.0f);
		rotation = glm::rotate(rotation, glm::radians((float)rotationEuler.X), glm::vec3(1.0f, 0.0f, 0.0f));
		rotation = glm::rotate(rotation, glm::radians((float)rotationEuler.Y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotation = glm::rotate(rotation, glm::radians((float)rotationEuler.Z), glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(transformID, 1, GL_FALSE, glm::value_ptr(transform));
		glUniformMatrix4fv(rotationID, 1, GL_FALSE, glm::value_ptr(rotation));
		glUniformMatrix4fv(scaleID, 1, GL_FALSE, glm::value_ptr(scale));
		shader->SetVector("color", color.r, color.g, color.b, color.a);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(GetDataVAO(thisVao));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void SpriteRenderer::DrawUpdate()
	{	
		Draw();
	}

	void SpriteRenderer::Start()
	{
		gmObj->transform->position.Z = -10 + 0.02 * priorityIndex + priorityOffSet * 0.0001;
		priorityOffSet++;
	}

	void SpriteRenderer::SetTexture(unsigned int& tex)
	{
		// tell opengl for each sampler to which texture unit it belongs to
		shader->Use(); // activate shader before setting uniforms

		texture = tex;
		shader->SetInt(textureID, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	VAO_DATA SpriteRenderer::GetDataVAO(VAOType type)
	{
		switch (type)
		{
		case ClusterEngine::SpriteRenderer::VAOType::SQUARE:
			return square;
			break;
		default:
			break;
		}
		return square;
	}

	int SpriteRenderer::GetPriorityIndex() const noexcept
	{
		return priorityIndex;
	}

	void SpriteRenderer::SetPriorityIndex(int index)
	{
		priorityIndex = index;
	}

	void SpriteRenderer::Dispose()
	{
		priorityOffSet--;
	}
}