#pragma once

#include "IO/ImageLoader.h"

class STBImageLoader: public ImageLoader {

public:
	STBImageLoader(bool verticallyFlipImage); 

	ImageInfo LoadImageFromPath(const std::string& path) const override;
	void FreeImageData(ImageInfo& imageInfo) const override;

private:
	bool m_VerticallyFlipImage = true; 

};
