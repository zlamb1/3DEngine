#pragma once

enum class DrawUsage : int {
	STATIC, DYNAMIC
};


class Mesh {

public:
	virtual ~Mesh() = default; 

	virtual void BindMesh() const = 0;
	virtual void BindVertexBuffer(unsigned int bindingindex, int offset, int stride) const = 0; 
	virtual void DrawMesh() const = 0;

	virtual void BufferData(unsigned int vertexCount, unsigned int vertexSize, 
		const void* data, DrawUsage drawUsage) = 0;

protected:
	unsigned int m_VertexCount = 0; 

};