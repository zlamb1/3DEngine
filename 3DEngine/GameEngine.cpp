#include "GameEngine.h"

#include "Logger.h"

#define ASSERT(x) if (!(x)) __debugbreak(); 

const std::string LOG_HEADER = "[3DEngine] : ";

#define FOV_Y glm::radians(90.0f)
#define Z_NEAR 0.01f
#define Z_FAR 100.0f 

GameEngine::GameEngine(IWindowCore& windowCore, RenderCore& renderCore) :
m_WindowCore(windowCore), m_RenderCore(renderCore) {
	
}


bool GameEngine::StartEngine() {
	LOG_INFO(LOG_HEADER + "Initializing Engine")

	ASSERT(m_WindowHnd)
	ASSERT(m_Camera)
	ASSERT(m_ImageLoader)

	// init cores and window handle
	if (!m_WindowCore.InitializeCore()) {
		LOG_ERROR(LOG_HEADER + "Failed to Initialize Window Core")
		return false; 
	}
	if (!m_WindowHnd->InitializeWindow()) {
		LOG_ERROR(LOG_HEADER + "Failed to Initialize Window Handle")
		return false; 
	} 
	if (!m_RenderCore.InitializeCore()) {
		LOG_ERROR(LOG_HEADER + "Failed to Initialize Render Core")
		return false; 
	}

	// init viewport size
	int width, height;
	m_WindowHnd->GetWindowSize(&width, &height);
	m_RenderCore.SetViewport(0, 0, width, height);

	// alloc key buffer
	for (int i = 0; i < 512; i++) {
		m_KeyBuffer.emplace_back(false);
	}

	m_WindowHnd->HookMouseMove([&](double xpos, double ypos) {
		if (m_WindowHnd->IsFocused()) {
			m_Camera->ProcessMouseMove(*m_WindowHnd, xpos, ypos);
		}
	});

	m_WindowHnd->HookKeyPress([&](int key, int action) {
		// store key press to buffer
		m_KeyBuffer[key] = !action ? false : true;
	});

	m_WindowHnd->HookWindowResize([&](const int w, const int h) {
		// resize viewport on window resize
		m_RenderCore.SetViewport(0, 0, w, h);
		// regenerate projection matrix
		m_Projection = CameraUtility::CreateProjectionMatrix(FOV_Y,
			m_WindowHnd->GetAspectRatio(), Z_NEAR, Z_FAR);
	});

	m_WindowHnd->HookMouseScroll([&](double xoffset, double yoffset) {
		if (m_WindowHnd->IsFocused()) {
			m_Camera->ProcessMouseScroll(*m_WindowHnd, xoffset, yoffset);
		}
	});

	// init projection matrix
	m_Projection = CameraUtility::CreateProjectionMatrix(FOV_Y,
		m_WindowHnd->GetAspectRatio(), Z_NEAR, Z_FAR);

	if (!SetupEngine()) {
		LOG_ERROR(LOG_HEADER << "Failed to Setup Engine"); 
		return false;
	}

	return true;
}

void GameEngine::StartRenderLoop() {
	while (!m_WindowHnd->QueryCloseRequested()) {
		// notify render core of frame
		m_RenderCore.OnFrame();
		// render frame
		OnFrame(); 
		// clean up
		m_WindowHnd->SwapBuffers();
		m_WindowCore.PollEvents();
		m_Camera->ProcessKeyInput(*m_WindowHnd, m_KeyBuffer);
	}
}

void GameEngine::ShutdownEngine() const {
	LOG_INFO(LOG_HEADER + "Shutting Down Engine")
	m_RenderCore.ShutdownCore();
	m_WindowHnd->DestroyWindow(); 
	m_WindowCore.ShutdownCore();
}