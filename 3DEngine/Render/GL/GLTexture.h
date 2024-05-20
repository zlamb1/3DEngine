#pragma once

#include "GLRenderCore.h"
#include "IO/ImageLoader.h"

class GLTexture: public ITexture {

public:
	GLTexture(const ImageLoader::ImageProfile& profile);
	~GLTexture() override; 

	void BindTexture() const override;

private:
	unsigned int m_TexId = -1; 
	int m_ImageWidth = 0, m_ImageHeight = 0, m_ImageChannels = 0; 

};
