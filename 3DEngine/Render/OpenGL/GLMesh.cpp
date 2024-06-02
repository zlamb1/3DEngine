#include "GLMesh.h"

#include <glad/glad.h>

#include "GLRenderCore.h"

GLMesh::GLMesh() {
	GLCall(glGenBuffers(1, &m_VBO))
}

GLMesh::~GLMesh() {
	GLCall(glDeleteBuffers(1, &m_VBO))
}

void GLMesh::BindMesh() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO))
}

void GLMesh::BindVertexBuffer(unsigned int bindingindex, int offset, int stride) const {
	GLCall(glBindVertexBuffer(bindingindex, m_VBO, offset, stride))
}

void GLMesh::DrawMesh() const {
	BindMesh();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, m_VertexCount)) 
}

void GLMesh::BufferData(unsigned int vertexCount, unsigned int vertexSize, 
	const void* data, DrawUsage drawUsage) {
	GLenum usage = GL_STATIC_DRAW;
	switch (drawUsage) {
		case DrawUsage::STATIC:
			usage = GL_STATIC_DRAW;
			break;
		case DrawUsage::DYNAMIC:
			usage = GL_DYNAMIC_DRAW;
			break;
	}

	BindMesh(); 
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexSize, data, usage))
	m_VertexCount = vertexCount; 
}
