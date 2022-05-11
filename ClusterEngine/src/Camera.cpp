#include "Camera.h"

#include "Time.h"

namespace ClusterEngine
{
	Camera::Camera(float cameraSize) :
		cameraSize(cameraSize), Component() {}

	void Camera::SetCameraSize(float cameraSize)
	{
		this->cameraSize = cameraSize;
		SetProperties(WindowSettings::GetWidth(), WindowSettings::GetHeight());
	}

	float Camera::GetCameraWidth() const
	{
		return cameraWidth;
	}

	float Camera::GetCameraHeight() const
	{
		return cameraHeight;
	}

	float Camera::GetCameraSize() const
	{
		return cameraSize;
	}

	Vector2 Camera::GetMousePosWorldSpace() const
	{
		return mousePositionWorldSpace;
	}

	void Camera::Start()
	{
		//get the projection id of the shader 
		projectionID = glGetUniformLocation(StandardShaders::simpleShader.ID, "projection");
		SetCameraSize(cameraSize);
		WindowSettings::OnWindowSizeModified.Add(&Camera::SetProperties, *this);
		SetProjection();
	}

	void Camera::Update()
	{
		glm::vec4 mouseWS = GetViewProjectionInverse() *
			glm::vec4(
				(InputsHandler::GetMousePosition().X - WindowSettings::GetWidth() * .5f) / WindowSettings::GetWidth(),
				-(InputsHandler::GetMousePosition().Y - WindowSettings::GetHeight() * .5f) / WindowSettings::GetHeight()
				, 1.0f, 1.0f
			);
		mousePositionWorldSpace = Vector2(mouseWS.x, mouseWS.y) * 2;	
	}

	void Camera::DrawUpdate()
	{
		SetProjection();
	}

	Camera::~Camera() {}

	void Camera::SetProperties(float width, float height)
	{
		float widthPerHeight = (float)WindowSettings::GetWidth() / (float)WindowSettings::GetHeight();
		cameraHeight = cameraSize * 0.5f;

		cameraWidth = widthPerHeight * cameraHeight;
	}

	void Camera::SetProjection() const
	{
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(GetViewProjection()));
	}

	glm::mat4 Camera::GetViewProjection() const
	{
		Vector3 position = gmObj->transform->position;
		Vector3 rot = Quaternion::ToEuler(gmObj->transform->rotation);

		glm::mat4 projection(1.0f);

		projection = glm::ortho(-cameraWidth, cameraWidth, -cameraHeight, cameraHeight, -10.0f, 100.0f);
		projection = glm::rotate(projection, -(float)rot.Z, glm::vec3(0.0f, 0.0f, 1.0f));
		projection = glm::translate(projection, glm::vec3(-position.X, -position.Y, -position.Z));
		return projection;
	}

	glm::mat4 Camera::GetViewProjectionInverse() const
	{
		return glm::inverse(GetViewProjection());
	}
}