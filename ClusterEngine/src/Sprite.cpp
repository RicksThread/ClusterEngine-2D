#include "Sprite.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

namespace ClusterEngine
{
	Sprite::Sprite() : tex(std::shared_ptr<TEXTURE>(new TEXTURE)) 
	{}

	Sprite::Sprite(const char* path) : path(path), tex(std::shared_ptr<TEXTURE>(new TEXTURE))
	{
		data = stbi_load(path, &width, &height, &nrChannels, 0);
	}

	void Sprite::SetPath(const char* path)
	{
		this->path = path;
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

	void Sprite::CreateTexture()
	{
		if (!IsPathInitialized())
		{	
			std::cout << "Couldn't create texture! path was null!\n";
			return;
		}
		if (!isImageTaken) LoadImage();
		if (isTextureCreated) return;
		isTextureCreated = true;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// load image, create texture and generate mipmaps

		glGenTextures(1, tex.get());
		glBindTexture(GL_TEXTURE_2D, *tex.get());

		if (data)
		{
			if (GetIsTransparent())
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GetWidth(), GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GetWidth(), GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

	}

	TEXTURE* Sprite::GetTexture()
	{
		return tex.get();
	}

	void Sprite::Dispose()
	{
		glDeleteTextures(1, tex.get());
	}

	void Sprite::LoadImage()
	{
		if (!IsPathInitialized())
		{
			std::cout << "Path not initialized!\n";
			return;
		}
		isImageTaken = true;
		data = stbi_load(path, &width, &height, &nrChannels, 0);
	}

	bool Sprite::IsPathInitialized() const noexcept
	{
		return (path != nullptr);
	}

	Sprite::~Sprite()
	{
		Dispose();
	}
}
