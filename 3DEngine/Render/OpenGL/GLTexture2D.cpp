#include "GLTexture2D.h"

GLTexture2D::GLTexture2D(const ImageInfo& imageInfo) {
	m_ImageWidth = imageInfo.m_ImageWidth;
	m_ImageHeight = imageInfo.m_ImageHeight;
	m_ImageChannels = imageInfo.m_ImageChannels;
	if (!imageInfo.m_ImageData) {
		LOG_WARN("[GLTexture2D] Attempted to Create Texture With Invalid Image Data");
	}
	else {
		GLCall(glGenTextures(1, &m_TextureId))
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureId))

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT))
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT))
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR))
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_ImageWidth, m_ImageHeight, 
			0, GL_RGB, GL_UNSIGNED_BYTE, imageInfo.m_ImageData))
		GLCall(glGenerateMipmap(GL_TEXTURE_2D))
	}
}

GLTexture2D::~GLTexture2D() {
	GLCall(glDeleteTextures(1, &m_TextureId))
}


void GLTexture2D::Bind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureId))
}
