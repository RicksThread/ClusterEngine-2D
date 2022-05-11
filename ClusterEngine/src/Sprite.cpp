#include "Sprite.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

namespace ClusterEngine
{
	Sprite::Sprite(const char* path)
	{
		data = stbi_load(path, &width, &height, &nrChannels, 0);
	}

	void Sprite::SetIsFlipped(bool state)
	{
		stbi_set_flip_vertically_on_load(state);
	}

	bool Sprite::GetIsTransparent() const noexcept
	{
		return nrChannels >= 4;
	}

	int Sprite::GetNChannels() const noexcept
	{
		return nrChannels;
	}

	int Sprite::GetWidth() const noexcept
	{
		return width;
	}

	int Sprite::GetHeight() const noexcept
	{
		return height;
	}

	void Sprite::Dispose()
	{
		if (!isCleaned)
			stbi_image_free(data);
	}

	Sprite::~Sprite()
	{
		Dispose();
	}
}
