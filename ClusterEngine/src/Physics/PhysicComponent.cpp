#include "PhysicComponent.hpp"

namespace ClusterEngine
{
	namespace Physics
	{
		std::vector<PhysicComponent*> PhysicComponent::physicComponents(0);

		PhysicComponent::PhysicComponent()
		{
			using std::unique_ptr;
			physicComponents.push_back(this);
		}

		PhysicComponent::~PhysicComponent()
		{
			using std::unique_ptr;

			if (physicComponents.size() == 0) return;

			auto isThisPsComp = [&](PhysicComponent* psCmp) { return psCmp == this; };
			auto it = std::find_if(physicComponents.begin(), physicComponents.end(), isThisPsComp);
			physicComponents.erase(it);
		}
	}
}