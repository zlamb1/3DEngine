#include "STBImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Logger.h"

STBImageLoader::STBImageLoader(bool verticallyFlipImage) : m_VerticallyFlipImage(verticallyFlipImage) {}

ImageLoader::ImageProfile STBImageLoader::LoadImageFromPath(const std::string& path) const {
	stbi_set_flip_vertically_on_load(m_VerticallyFlipImage);
	ImageLoader::ImageProfile profile{};
	profile.m_ImageData = stbi_load(path.c_str(),
		&profile.m_ImageWidth, &profile.m_ImageHeight, &profile.m_ImageChannels, 0);
	if (!profile.m_ImageData) {
		// image load failed
		LOG_WARN("[STBImageLoader] Failed to Load Image at Path: " << path); 
	}

	return profile; 
}

void STBImageLoader::FreeImageData(ImageProfile& profile) const {
	if (profile.m_ImageData) stbi_image_free(profile.m_ImageData);
	else LOG_WARN("[STBImageLoader] Attempt to Free Nullptr Image Data"); 
}
