#include "Transform.h"

namespace ClusterEngine
{
	Transform::Transform(Vector3 position, Quaternion rotation, Vector3 scale) : position(position), rotation(rotation), scale(scale) {}

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
		if (transform == nullptr)
		{
			if (parent != nullptr)
				parent->RemoveChild(this);
			parent = nullptr;
		}
		else
		{
			if (parent != nullptr)
				parent->RemoveChild(this);
			parent = transform;
			parent->AddChild(this);
		}
	}

	void Transform::AddChild(Transform* transform)
	{
		children.insert(transform);
	}

	void Transform::RemoveChild(Transform* transform)
	{
		if (children.count(transform)) return;
		children.erase(transform);
	}

	Transform* Transform::GetParent() const
	{
		return parent;
	}

	Transform* Transform::GetChild(int i) const
	{
		int index = 0;
		for (const auto& child : children)
		{
			if (index == i) return child;
			index++;
		}
		return nullptr;
	}

	int Transform::GetChildCount() const
	{
		return children.size();
	}
}