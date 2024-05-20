#pragma once
#include "GameEngine.h"

class BlockGameEngine: public GameEngine {

public:
	BlockGameEngine();

	bool SetupEngine() override;
	void OnFrame() override;

private:
	std::unique_ptr<IAttribLayout> m_ShaderLayout; 
	std::unique_ptr<IShader> m_ChunkShader;
	unsigned int m_VBO; 

};
