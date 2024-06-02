#pragma once

#include "Render/Mesh.h"

class GLMesh: public Mesh {

public:
	GLMesh();
	~GLMesh() override;

	void BindMesh() const override;
	void BindVertexBuffer(unsigned int bindingindex, int offset, int stride) const override;
	void DrawMesh() const override;

	void BufferData(unsigned int vertexCount, unsigned int vertexSize, 
		const void* data, DrawUsage drawUsage) override;

private:
	unsigned int m_VBO; 

};
