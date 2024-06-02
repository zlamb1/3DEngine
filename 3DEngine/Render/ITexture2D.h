#pragma once

#include "ITexture.h"
#include "Ref.h"

#include "IO/ImageLoader.h"

class ITexture2D : public ITexture {
public:

	static Ref<ITexture> CreateTexture2D(const ImageInfo& imageInfo);

};
