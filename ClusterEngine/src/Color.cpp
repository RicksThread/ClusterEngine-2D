#include "Color.h"

#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"

namespace ClusterEngine
{

	Color::Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b)
	{}

	Color::Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a)
	{}

	Color::Color(Vector3 color, float _a) : r(color.X), g(color.Y), b(color.Z), a(_a) 
	{}

	Color::Color(Vector3 color) : r(color.X), g(color.Y), b(color.Z), a(0) 
	{}

	Color Color::operator + (Color const& otherColor) noexcept
	{
		Color newColor(this->r, this->g, this->b, this->a);
		newColor.r += otherColor.r;
		newColor.g += otherColor.g;
		newColor.b += otherColor.b;
		newColor.a += otherColor.a;

		return newColor;
	}

	Color Color::operator - (Color const& otherColor) noexcept
	{
		Color newColor(this->r, this->g, this->b, this->a);
		newColor.r -= otherColor.r;
		newColor.g -= otherColor.g;
		newColor.b -= otherColor.b;
		newColor.a -= otherColor.a;

		return newColor;
	}

	Color Color::operator * (Color const& otherColor) noexcept
	{
		Color newColor(this->r, this->g, this->b, this->a);
		newColor.r *= otherColor.r;
		newColor.g *= otherColor.g;
		newColor.b *= otherColor.b;
		newColor.a *= otherColor.a;

		return newColor;
	}

	Color Color::operator / (Color const& otherColor) 
	{
		Color newColor(this->r, this->g, this->b, this->a);
		newColor.r /= otherColor.r;
		newColor.g /= otherColor.g;
		newColor.b /= otherColor.b;
		newColor.a /= otherColor.a;

		return newColor;
	}

	Color Color::operator + (float const& value) noexcept
	{
		Color newColor(this->r, this->g, this->b, this->a);
		newColor.r += value;
		newColor.g += value;
		newColor.b += value;
		newColor.a += value;

		return newColor;
	}

	Color Color::operator - (float const& value) noexcept
	{
		Color newColor(this->r, this->g, this->b, this->a);
		newColor.r -= value;
		newColor.g -= value;
		newColor.b -= value;
		newColor.a -= value;

		return newColor;
	}

	Color Color::operator * (float const& value) noexcept
	{
		Color newColor(this->r, this->g, this->b, this->a);
		newColor.r *= value;
		newColor.g *= value;
		newColor.b *= value;
		newColor.a *= value;

		return newColor;
	}

	Color Color::operator / (float const& value) 
	{
		Color newColor(this->r, this->g, this->b, this->a);
		newColor.r /= value;
		newColor.g /= value;
		newColor.b /= value;
		newColor.a /= value;

		return newColor;
	}

	Color Color::Black() noexcept
	{
		return Color(0, 0, 0, 1);
	}

	Color Color::White() noexcept
	{
		return Color(1, 1, 1, 1);
	}

	Color Color::Green() noexcept
	{
		return Color(0, 1, 0, 1);
	}

	Color Color::Red()  noexcept
	{
		return Color(1, 0, 0, 1);
	}
 
	Color Color::Blue() noexcept
	{
		return Color(0, 0, 1, 1);
	}

	Vector3 Color::operator = (Color const& otherColor)
	{
		return Vector3(otherColor.r, otherColor.g, otherColor.b);
	}

	Color Color::operator = (Vector3 const& vet)
	{
		r = vet.X;
		g = vet.Y;
		b = vet.Z;
		return *this;
	}
}

