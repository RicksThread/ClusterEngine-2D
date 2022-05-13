#pragma once
#include "Image.h"
#include "Component.h"
#include "GameObject.h"
#include "Math/Quaternion.hpp"
#include "Math/Vector3.hpp"
#include "Transform.h"

class ResourceManager
{
public:
	static Image CreateImage(const char* path);

	static void DisposeImage(Image* image);

	static void FlipVerticalImage(bool flipVertical);


private:
	ResourceManager();
};