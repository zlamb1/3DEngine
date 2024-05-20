#pragma once

#include "Window/IWindowCore.h"
#include "Window/WindowHnd.h"
#include "Render/RenderCore.h"

class GameEngine {

public:
	GameEngine(IWindowCore& windowCore, RenderCore& renderCore); 
	virtual ~GameEngine() = default;

	bool StartEngine();
	void StartRenderLoop();
	void ShutdownEngine() const;

	virtual bool SetupEngine() = 0;
	virtual void OnFrame() = 0; 

protected:
	IWindowCore& m_WindowCore;
	RenderCore& m_RenderCore;

	std::shared_ptr<WindowHnd> m_WindowHnd = nullptr;
	std::shared_ptr<Camera> m_Camera = nullptr;
	std::shared_ptr<ImageLoader> m_ImageLoader = nullptr;

	std::vector<bool> m_KeyBuffer{};
	glm::mat4 m_Projection{};

};