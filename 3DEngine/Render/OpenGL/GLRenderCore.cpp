#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLRenderCore.h"

#include "GLAttribLayout.h"
#include "GLMesh.h"
#include "GLShader.h"
#include "GLTexture2D.h"

#include "IO/ImageLoader.h"

bool GLRenderCore::InitializeCore() {
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void GLRenderCore::ShutdownCore() {
	// glad doesn't require any deinit
}

void GLRenderCore::OnFrame() {
	GLCall(glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
}

void GLRenderCore::SetViewport(int x, int y, int width, int height) {
	GLCall(glViewport(x, y, width, height))
}

void GLRenderCore::SetCullFace(FaceType faceType) {
	GLenum mode = GL_BACK;
	switch (faceType) {
		case FaceType::BACK:
			mode = GL_BACK;
			break;
		case FaceType::FRONT:
			mode = GL_FRONT;
			break;
		case FaceType::FRONT_AND_BACK:
			mode = GL_FRONT_AND_BACK;
			break;
	}

	GLCall(glCullFace(mode))
}


void GLRenderCore::SetFrontFace(WindingOrder windingOrder) {
	GLenum mode = GL_CCW;
	switch (windingOrder) {
		case WindingOrder::CW:
			mode = GL_CW;
			break;
		case WindingOrder::CCW:
			mode = GL_CCW;
			break;
	}

	GLCall(glFrontFace(mode)) 
}


void GLRenderCore::EnableDepthTesting(bool enabled) {
	if (enabled) {
		GLCall(glEnable(GL_DEPTH_TEST))
	} else {
		GLCall(glDisable(GL_DEPTH_TEST))
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
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE))
	} else {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL))
	}
}

Ref<IAttribLayout> GLRenderCore::CreateAttribLayout() const {
	return CreateRef<GLAttribLayout>();
}

Ref<Mesh> GLRenderCore::CreateMesh() const {
	return CreateRef<GLMesh>();
}


Ref<IShader> GLRenderCore::CreateShader(std::string_view vertSource, std::string_view fragSource) const {
	return CreateRef<GLShader>(vertSource, fragSource);
}

Ref<ITexture> GLRenderCore::CreateTexture2D(const ImageInfo& imageInfo) const {
	return CreateRef<GLTexture2D>(imageInfo);
}