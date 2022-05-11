#pragma once

namespace ClusterEngine
{
	class Utilities
	{
	public:
		template<typename T>
		static void Exchange(T& a, T& b);
	};

	template<typename T>
	void Utilities::Exchange(T& a, T& b)
	{
		T aCont = a;
		a = b;
		b = aCont;
	}
}