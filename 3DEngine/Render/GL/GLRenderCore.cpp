#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLRenderCore.h"

#include "GLAttribLayout.h"
#include "GLMesh.h"
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

void GLRenderCore::SetCullFace(RenderUtil::CullFace cullFace) {
	GLenum mode = GL_BACK;
	switch (cullFace) {
		case RenderUtil::BACK:
			mode = GL_BACK;
			break;
		case RenderUtil::FRONT:
			mode = GL_FRONT;
			break;
		case RenderUtil::FRONT_AND_BACK:
			mode = GL_FRONT_AND_BACK;
			break;
	}

	GLCall(glCullFace(mode));
}


void GLRenderCore::SetFrontFace(RenderUtil::FrontFace frontFace) {
	GLenum mode = GL_CCW;
	switch (frontFace) {
		case RenderUtil::CW:
			mode = GL_CW;
			break;
		case RenderUtil::CCW:
			mode = GL_CCW;
			break;
	}

	GLCall(glFrontFace(mode)) 
}


void GLRenderCore::EnableDepthTesting(bool enabled) {
	if (enabled) {
		GLCall(glEnable(GL_DEPTH_TEST));
	} else {
		GLCall(glDisable(GL_DEPTH_TEST));
	}
}

void GLRenderCore::EnableFaceCulling(bool enabled) {
	if (enabled) {
		GLCall(glEnable(GL_CULL_FACE)) 
	} else {
		GLCall(glDisable(GL_CULL_FACE))
	}
}

void GLRenderCore::EnableWireframeMode(bool enabled) {
	if (enabled) {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	} else {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	}
}


unique_ptr<IAttribLayout> GLRenderCore::CreateAttribLayout() const {
	return std::make_unique<GLAttribLayout>();
}

unique_ptr<Mesh> GLRenderCore::CreateMesh() const {
	return std::make_unique<GLMesh>();
}


unique_ptr<IShader> GLRenderCore::CreateShader(std::string_view vertSource, std::string_view fragSource) const {
	return std::make_unique<GLShader>(vertSource, fragSource); 
}


unique_ptr<ITexture> GLRenderCore::CreateTexture(const ImageLoader::ImageProfile& profile) const {
	return std::make_unique<GLTexture>(profile); 
}