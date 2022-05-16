#include "ResourceManager.h"

#ifndef STB_IMAGE_IMPLEMENTATION    
#define STB_IMAGE_IMPLEMENTATION   
#include "stb_image.h"
#endif

Image ResourceManager::CreateImage(const char* path)
{
	Image newImage;
	newImage.data = stbi_load(path, &newImage.width, &newImage.height, &newImage.nrChannels, 0);
	return newImage;
}

void ResourceManager::DisposeImage(Image* image)
{
	stbi_image_free(image->data);
}

void ResourceManager::FlipVerticalImage(bool flipVertical)
{
	stbi_set_flip_vertically_on_load(flipVertical);
}
