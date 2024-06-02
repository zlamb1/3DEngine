#include "ITexture2D.h"

#include "RendererAPI.h"

Ref<ITexture> ITexture2D::CreateTexture2D(const ImageInfo& imageInfo) {
	return RendererAPI::Instance().GetRenderCore().CreateTexture2D(imageInfo); 
}
