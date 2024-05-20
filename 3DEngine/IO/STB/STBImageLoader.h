#pragma once

#include "IO/ImageLoader.h"

class STBImageLoader: public ImageLoader {

public:
	STBImageLoader(bool verticallyFlipImage); 

	ImageProfile LoadImageFromPath(const std::string& path) const override;
	void FreeImageData(ImageProfile& profile) const override; 

private:
	bool m_VerticallyFlipImage = true; 

};
