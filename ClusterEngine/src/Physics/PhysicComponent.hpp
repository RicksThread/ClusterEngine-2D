#pragma once
#include <vector>
#include <memory>
#include <unordered_set>
#include "../Component.h"
#include <iostream>

namespace ClusterEngine
{
	namespace Physics
	{
		class PhysicsManager;

		class PhysicComponent : public Component
		{
		public:
			PhysicComponent();
			virtual ~PhysicComponent() override;
		protected:

			virtual void FixedUpdate() {}

		private:
			friend PhysicsManager;
			static std::vector<PhysicComponent*> physicComponents;
		};
	}
}