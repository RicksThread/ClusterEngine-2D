#pragma once

class Vector3;

namespace ClusterEngine
{

	struct Color
	{
	public:
		float r, g, b, a;

		Color() = delete;
		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);
		Color(Vector3 color, float a);
		Color(Vector3 color);

		Color operator + (Color const& otherColor) noexcept;
		Color operator - (Color const& otherColor) noexcept;
		Color operator * (Color const& otherColor) noexcept;
		Color operator / (Color const& otherColor);
		Color operator + (float const& value) noexcept;
		Color operator - (float const& value) noexcept;
		Color operator * (float const& value) noexcept;
		Color operator / (float const& value);

		Vector3 operator = (Color const& otherColor);

		Color operator = (Vector3 const& vet);

		static Color Black() noexcept;
		static Color White() noexcept;
		static Color Green() noexcept;
		static Color Red() noexcept;
		static Color Blue() noexcept;
	};
}
