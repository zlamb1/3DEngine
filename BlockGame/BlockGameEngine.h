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
	Ref<IAttribLayout> m_ShaderLayout;
	Ref<IShader> m_ChunkShader;
	Ref<Chunk> m_Chunk; 

	Scope<Player> m_Player;

	StateTracker<bool> m_Wireframe{ false, 0.3 }; 
};
