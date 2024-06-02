#pragma once

#include <memory>
#include <vector>

#include "Ref.h"

#include "Render/Mesh.h"

constexpr int CHUNK_WIDTH = 32, CHUNK_DEPTH = 32, CHUNK_HEIGHT = 16;

namespace ChunkUtilty {
	static int PositionToIndex(int x, int y, int z) {
		return z + (y * CHUNK_DEPTH) + (x * CHUNK_DEPTH * CHUNK_HEIGHT);
	}

	static void IndexToPosition(int index, int* x, int* y, int* z) {
		*z = index % CHUNK_DEPTH;
		*y = index / CHUNK_DEPTH % CHUNK_HEIGHT;
		*x = index / CHUNK_DEPTH / CHUNK_HEIGHT;
	}
}

class Chunk {

public:
	Chunk(Ref<Mesh> chunkMesh);

	void CreateMesh() const; 
	void DrawChunk() const; 

private:
	int m_X = 0, m_Y = 0, m_Z = 0; 
	std::vector<unsigned short> m_Blocks{}; 
	Ref<Mesh> m_ChunkMesh; 
};
