#include "STBImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Logger.h"

STBImageLoader::STBImageLoader(bool verticallyFlipImage) : m_VerticallyFlipImage(verticallyFlipImage) {}

ImageInfo STBImageLoader::LoadImageFromPath(const std::string& path) const {
	stbi_set_flip_vertically_on_load(m_VerticallyFlipImage);
	ImageInfo imageInfo; 
	imageInfo.m_ImageData = stbi_load(path.c_str(),
		&imageInfo.m_ImageWidth, &imageInfo.m_ImageHeight, &imageInfo.m_ImageChannels, 0);
	if (!imageInfo.m_ImageData) {
		// image load failed
		LOG_WARN("[STBImageLoader] Failed to Load Image at Path: " << path)
	}

	return imageInfo;
}

void STBImageLoader::FreeImageData(ImageInfo& imageInfo) const {
	if (imageInfo.m_ImageData) stbi_image_free(imageInfo.m_ImageData);
	else LOG_WARN("[STBImageLoader] Attempt to Free Nullptr Image Data")
}
