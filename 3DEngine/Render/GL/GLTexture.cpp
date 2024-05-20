#include "GLTexture.h"

GLTexture::GLTexture(const ImageLoader::ImageProfile& profile) {
	m_ImageWidth = profile.m_ImageWidth;
	m_ImageHeight = profile.m_ImageHeight;
	m_ImageChannels = profile.m_ImageChannels;
	if (!profile.m_ImageData) {
		LOG_WARN("[GLTexture] Attempted to Create Texture With Invalid Image Data");
	}
	else {
		GLCall(glGenTextures(1, &m_TexId));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TexId));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_ImageWidth, m_ImageHeight, 
			0, GL_RGB, GL_UNSIGNED_BYTE, profile.m_ImageData));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
}

GLTexture::~GLTexture() {
	GLCall(glDeleteTextures(1, &m_TexId)); 
}


void GLTexture::BindTexture() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TexId));
}
