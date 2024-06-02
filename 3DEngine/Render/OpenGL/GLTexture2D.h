#pragma once

#include "GLRenderCore.h"
#include "IO/ImageLoader.h"

class GLTexture2D: public ITexture2D {

public:
	GLTexture2D(const ImageInfo& imageInfo);
	~GLTexture2D() override; 

	void Bind() const override;

private:
	unsigned int m_TextureId = -1; 
	int m_ImageWidth = 0, m_ImageHeight = 0, m_ImageChannels = 0; 

};
