#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLRenderCore.h"

#include "GLAttribLayout.h"
#include "GLShader.h"
#include "GLTexture.h"

#include "IO/ImageLoader.h"

bool GLRenderCore::InitializeCore() {
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void GLRenderCore::ShutdownCore() {
	// glad doesn't require any deinit
}

void GLRenderCore::OnFrame() {
	GLCall(glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GLRenderCore::SetViewport(int x, int y, int width, int height) {
	GLCall(glViewport(x, y, width, height));
}

void GLRenderCore::SetDepthTest(bool enable) {
	if (enable) {
		GLCall(glEnable(GL_DEPTH_TEST));
	} else {
		GLCall(glDisable(GL_DEPTH_TEST));
	}
}

unique_ptr<IAttribLayout> GLRenderCore::CreateAttribLayout() {
	return std::make_unique<GLAttribLayout>();
}


unique_ptr<IShader> GLRenderCore::CreateShader(std::string_view vertSource, std::string_view fragSource) const {
	return std::make_unique<GLShader>(vertSource, fragSource); 
}


unique_ptr<ITexture> GLRenderCore::CreateTexture(const ImageLoader::ImageProfile& profile) const {
	return std::make_unique<GLTexture>(profile); 
}