#pragma once
#include "Math/Vector3.hpp"
#include "Math/Quaternion.hpp"
#include "Component.h"
#include <vector>

namespace ClusterEngine
{
	class Transform;

	class Transform : public Component
	{
	public:
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		Transform(Vector3 position, Quaternion rotation, Vector3 scale);

		virtual void Start() override {}
		virtual void Update() override;
		virtual void DrawUpdate() override;

		Vector3 PointWorldToLocalSpace(Vector3 point);

		Vector3 DirWorldToLocalSpace(Vector3 dir);

		Vector3 PointLocalToWorldSpace(Vector3 point);

		Vector3 DirLocalToWorldSpace(Vector3 dir);

		Vector3 GetUpDir();

		Vector3 GetRightDir();

		Vector3 GetForwardDir();

		void SetParent(Transform* transform);

		Transform* GetParent() const;
		Transform* GetChild(int i) const;
		int GetChildCount() const;

	private:
		friend class Transform;

		std::vector<Transform*> children;
		Transform* parent;

		Quaternion previousRot;
		Vector3 previousPos;
		Vector3 previousScale;

		void AddChild(Transform* transform);
	};
}