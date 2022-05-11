#include "Collider2D.hpp"

#include <algorithm>

namespace ClusterEngine
{
	namespace Physics
	{
		std::vector<Collider2D*> Collider2D::colliders(0);

		Collider2D::Collider2D(bool isTriggerer) : isTriggerer(isTriggerer)
		{
			colliders.push_back(this);
		}

		Collider2D::~Collider2D()
		{
			//remove the collider from the list of colliders
			auto it = std::remove_if(colliders.begin(), colliders.end(), [&](Collider2D* collider) {return collider == this; });

			colliders.erase(it);
		}
	}
}