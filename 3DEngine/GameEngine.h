#pragma once

#include "Ref.h"

#include "Entity/Player.h"

#include "Window/IWindowCore.h"
#include "Window/WindowHnd.h"
#include "Render/RenderCore.h"

#include "Time/FrameTime.h"

class GameEngine {

public:
	GameEngine(IWindowCore& windowCore); 
	virtual ~GameEngine() = default;

	bool StartEngine();
	void StartRenderLoop();
	void ShutdownEngine() const;

	virtual bool SetupEngine() = 0;
	virtual void OnFrame() = 0; 

protected:
	static RenderCore& GetRenderCore(); 

protected:
	IWindowCore& m_WindowCore;

	Ref<WindowHnd> m_Window;
	Ref<ImageLoader> m_ImageLoader;

	std::vector<KeyAction> m_KeyBuffer{};

	float m_AspectRatio = 0.0f; 
	glm::mat4 m_Projection{};

	FrameTime m_FrameTime{};

private:
	void CreateProjectionMatrix(); 

};
