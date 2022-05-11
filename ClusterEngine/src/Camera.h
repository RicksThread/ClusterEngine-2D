#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include "Component.h"
#include "Math/Vector3.hpp"
#include "Math/Vector2.hpp"
#include "WindowSettings.h"
#include "StandardShaders.h"
#include "InputsHandler.h"

namespace ClusterEngine
{
	class Camera : public Component
	{
	public:

		Camera(float cameraSize);
		void SetCameraSize(float cameraSize);
		inline float GetCameraWidth() const;
		inline float GetCameraHeight() const;
		inline float GetCameraSize() const;
		Vector2 GetMousePosWorldSpace() const;

		glm::mat4 GetViewProjection() const;
		glm::mat4 GetViewProjectionInverse() const;
	protected:
		void Start() override;
		void Update() override;
		void DrawUpdate() override;
		~Camera();
	private:
		ClusterEngine::Shader* viewShader;

		float cameraSize;
		float cameraWidth, cameraHeight;
		Vector2 mousePositionWorldSpace;

		unsigned int projectionID;
		void SetProperties(float width, float height);
		void SetProjection() const;
	};
}