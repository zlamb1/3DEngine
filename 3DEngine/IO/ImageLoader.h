#pragma once

#include <string>

struct ImageInfo {
	unsigned char* m_ImageData;
	int m_ImageWidth, m_ImageHeight, m_ImageChannels;
};

class ImageLoader {

public:
	virtual ~ImageLoader() = default; 

	virtual ImageInfo LoadImageFromPath(const std::string& path) const = 0;
	virtual void FreeImageData(ImageInfo& profile) const = 0;

};
