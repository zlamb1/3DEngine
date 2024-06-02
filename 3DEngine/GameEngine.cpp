#include "GameEngine.h"

#include <GLFW/glfw3.h>

#include "Logger.h"

#include "Event/Input/KeyPressEvent.h"
#include "Event/Input/WindowResizeEvent.h"

#include "Render/RendererAPI.h"

#define ASSERT(x) if (!(x)) __debugbreak(); 

const std::string LOG_HEADER = "[3DEngine] : ";

#define FOV_Y glm::radians(90.0f)
#define Z_NEAR 0.01f
#define Z_FAR 100.0f 

GameEngine::GameEngine(IWindowCore& windowCore) :
m_WindowCore(windowCore) {
	
}

bool GameEngine::StartEngine() {
	LOG_INFO(LOG_HEADER + "Initializing Engine")

	ASSERT(m_Window)
	ASSERT(m_ImageLoader)

	// init cores and window handle
	if (!m_WindowCore.InitializeCore()) {
		LOG_ERROR(LOG_HEADER + "Failed to Initialize Window Core")
		return false; 
	}

	if (!m_Window->InitializeWindow()) {
		LOG_ERROR(LOG_HEADER + "Failed to Initialize Window Handle")
		return false; 
	}

	// initialize viewport size
	int width, height;
	m_Window->GetWindowSize(&width, &height);
	GetRenderCore().SetViewport(0, 0, width, height);

	// allocate key buffer
	for (int i = 0; i < 512; i++) {
		m_KeyBuffer.emplace_back(RELEASE);
	}

	auto& eventHandler = m_Window->GetEventDispatcher();

	eventHandler.Subscribe<KeyPressEvent>(
		std::make_shared<EventHandler<KeyPressEvent>>(
		[&](const KeyPressEvent& _event) {
			// store key press to buffer
			m_KeyBuffer[_event.key] = _event.action;
	}));

	eventHandler.Subscribe<WindowResizeEvent>(
		std::make_shared<EventHandler<WindowResizeEvent>>(
		[&](const WindowResizeEvent& _event) {
			// resize viewport on window resize
			GetRenderCore().SetViewport(0, 0, _event.width, _event.height);
			const float newAspectRatio = m_Window->GetAspectRatio(); 
			if (m_AspectRatio != newAspectRatio) {
				// regenerate projection matrix
				m_AspectRatio = newAspectRatio;
				CreateProjectionMatrix(); 
			}
	}));

	// init projection matrix
	m_AspectRatio = m_Window->GetAspectRatio();
	CreateProjectionMatrix();

	if (!SetupEngine()) {
		LOG_ERROR(LOG_HEADER << "Failed to Setup Engine")
		return false;
	}

	return true;
}

void GameEngine::StartRenderLoop() {
	glfwSwapInterval(0);
	while (!m_Window->QueryCloseRequested()) {
		// notify render core of frame
		GetRenderCore().OnFrame();
		// render frame
		OnFrame();
		// clean up
		m_Window->SwapBuffers();
		m_WindowCore.PollEvents();
		m_FrameTime.OnFrame();
	}
}

void GameEngine::ShutdownEngine() const {
	LOG_INFO(LOG_HEADER + "Shutting Down Engine")
	GetRenderCore().ShutdownCore();
	m_Window->DestroyWindow(); 
	m_WindowCore.ShutdownCore();
}

RenderCore& GameEngine::GetRenderCore() {
	return RendererAPI::Instance().GetRenderCore(); 
}

void GameEngine::CreateProjectionMatrix() {
	m_Projection = CameraUtility::CreateProjectionMatrix(FOV_Y,
		m_AspectRatio, Z_NEAR, Z_FAR);
}
