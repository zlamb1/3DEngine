#pragma once

#include <string>

class ImageLoader {

public:
	struct ImageProfile {
		unsigned char* m_ImageData; 
		int m_ImageWidth, m_ImageHeight, m_ImageChannels; 
	};

	virtual ImageProfile LoadImageFromPath(const std::string& path) const = 0;
	virtual void FreeImageData(ImageProfile& profile) const = 0;

};
