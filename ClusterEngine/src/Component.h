#pragma once

namespace ClusterEngine
{
	class Transform;
	class GameObject;

	class Component
	{
	public:
		GameObject* gmObj;

		Transform* GetTransform();

		Component();
		virtual ~Component();

	protected:

		/**
		*	 Called the moment the object is loaded in the scene
		*/
		virtual void Start();

		/**
		*	Called every frame
		*/
		virtual void Update();

		/**
		*	Called on draw time (later than fixedupdate and update)
		*/
		virtual void DrawUpdate();

		/**
		*	Safe destructor call
		*/
		virtual void Dispose();
	private:
		friend class GameObject;

		void SetGmObj(GameObject* gmObj);
		void UnSetGmObj();
	};
}