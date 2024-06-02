#include "GLAttribLayout.h"

#include <glad/glad.h>

#include "GLRenderCore.h"

GLAttribLayout::GLAttribLayout() {
	GLCall(glGenVertexArrays(1, &m_VAO));
}

GLAttribLayout::~GLAttribLayout() {
	GLCall(glDeleteVertexArrays(1, &m_VAO));
}

void GLAttribLayout::BindLayout() const {
	GLCall(glBindVertexArray(m_VAO));
}

void GLAttribLayout::EnableAttrib(unsigned int attribindex) const {
	GLCall(glEnableVertexAttribArray(attribindex));
}

void GLAttribLayout::DisableAttrib(unsigned attribindex) const {
	GLCall(glDisableVertexAttribArray(attribindex));
}

void GLAttribLayout::AttribFormat(unsigned int attribindex, int size, 
	AttribType type, bool normalized, unsigned relativeoffset) const {
	GLenum glType = GL_FLOAT;
	switch (type) {
		case AttribType::FLOAT:
			glType = GL_FLOAT;
			break;
	}

	GLCall(glVertexAttribFormat(attribindex, size, glType, normalized, relativeoffset)); 
}

void GLAttribLayout::AttribBinding(unsigned int attribindex, unsigned int bindingindex) const {
	GLCall(glVertexAttribBinding(attribindex, bindingindex)); 
}
