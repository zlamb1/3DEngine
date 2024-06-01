#pragma once
#include "GameEngine.h"

#include "Render/Chunk.h"

#include "Time/StateTracker.h"

class BlockGameEngine: public GameEngine {

public:
	BlockGameEngine();

	bool SetupEngine() override;
	void OnFrame() override;

private:
	std::unique_ptr<IAttribLayout> m_ShaderLayout;
	std::unique_ptr<IShader> m_ChunkShader;
	std::unique_ptr<Chunk> m_Chunk; 

	StateTracker<bool> m_Wireframe{ 0.3 }; 
};
