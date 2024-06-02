#include "Chunk.h"

#include "Vertex.h"

constexpr float CUBE_POSITIONS[] {
	// SOUTH
	0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
	// NORTH
	-0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
	// EAST
	-0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
	// WEST
	0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
	// TOP
	0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f,
	// BOTTOM
	-0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f
};

Chunk::Chunk(Ref<Mesh> chunkMesh) : m_ChunkMesh(std::move(chunkMesh)) {
	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				m_Blocks.emplace_back(1); 
			}
		}
	}

	CreateMesh(); 
}

void Chunk::CreateMesh() const {
	std::vector<Vertex> data{};
	const float chunkX = static_cast<float>(m_X) * CHUNK_WIDTH,
		chunkY = static_cast<float>(m_Y) * CHUNK_HEIGHT,
		chunkZ = static_cast<float>(m_Z) * CHUNK_DEPTH;

	for (int blockindex = 0; blockindex < static_cast<int>(m_Blocks.size()); blockindex++) {
		int x, y, z;
		ChunkUtilty::IndexToPosition(blockindex, &x, &y, &z);
		for (int face = 0; face < 6; face++) {
			const int index = face * 18;
			for (int j = index; j < index + 18; j += 3) {
				data.emplace_back(
					Vertex{
						CUBE_POSITIONS[j] + static_cast<float>(x) + chunkX,
						CUBE_POSITIONS[j + 1] + static_cast<float>(y) + chunkY,
						CUBE_POSITIONS[j + 2] + static_cast<float>(z) + chunkZ
					}
				);
			}
		}
	}

	m_ChunkMesh->BufferData(static_cast<int>(data.size()), sizeof(Vertex),
		&data[0], DrawUsage::STATIC);
}


void Chunk::DrawChunk() const {
	m_ChunkMesh->BindVertexBuffer(0, 0, sizeof(Vertex));
	m_ChunkMesh->DrawMesh();
}
