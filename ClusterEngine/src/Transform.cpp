#include "Transform.h"

namespace ClusterEngine
{
	Transform::Transform(Vector3 position, Quaternion rotation, Vector3 scale) : position(position), rotation(rotation), scale(scale), children(0) {}

	Vector3 Transform::PointWorldToLocalSpace(Vector3 point)
	{
		if (scale == 1)
			return Quaternion::Inverse(rotation) * (point - position);
		else
			return (Quaternion::Inverse(rotation) * (point - position)) / scale;
	}

	Vector3 Transform::DirWorldToLocalSpace(Vector3 dir)
	{
		if (scale == 1)
			return (Quaternion::Inverse(rotation) * dir);
		else
			return (Quaternion::Inverse(rotation) * dir) / scale;
	}

	Vector3 Transform::PointLocalToWorldSpace(Vector3 point)
	{
		return rotation * point * scale + position;
	}

	Vector3 Transform::DirLocalToWorldSpace(Vector3 dir)
	{
		Vector3 worldSpace = rotation * dir * scale;
		return worldSpace;
	}

	Vector3 Transform::GetUpDir()
	{
		return Vector3::Normalized(DirLocalToWorldSpace(Vector3::Up()));
	}

	Vector3 Transform::GetRightDir()
	{
		return Vector3::Normalized(DirLocalToWorldSpace(Vector3::Right()));
	}

	Vector3 Transform::GetForwardDir()
	{
		return Vector3::Normalized(DirLocalToWorldSpace(Vector3::Forward()));
	}

	void Transform::Update()
	{
		previousPos = position;
		previousRot = rotation;
		previousScale = scale;
	}

	void Transform::DrawUpdate()
	{
		if (parent == nullptr) return;


		if (parent->rotation != parent->previousRot)
		{
			rotation *= parent->rotation * Quaternion::Inverse(parent->previousRot);
			position = parent->PointLocalToWorldSpace(position - parent->previousPos);
		}
		else if (parent->position != parent->previousPos)
		{
			position += parent->position - parent->previousPos;
		}

		if (parent->scale != parent->previousScale)
			scale += parent->scale - parent->previousScale;
	}

	void Transform::SetParent(Transform* transform)
	{
		parent = transform;
		parent->AddChild(transform);
	}

	void Transform::AddChild(Transform* transform)
	{
		children.push_back(transform);
	}

	Transform* Transform::GetParent() const
	{
		return parent;
	}

	Transform* Transform::GetChild(int i) const
	{
		return children[i];
	}

	int Transform::GetChildCount() const
	{
		return children.size();
	}
}