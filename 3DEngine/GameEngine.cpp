#include "GameEngine.h"

#include <GLFW/glfw3.h>

#include "Logger.h"

#include "Event/Input/KeyPressEvent.h"
#include "Event/Input/MouseMoveEvent.h"
#include "Event/Input/MouseScrollEvent.h"
#include "Event/Input/WindowResizeEvent.h"

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
	ASSERT(m_Player)
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

	const auto mouseMoveHandler = std::make_shared<EventHandler<MouseMoveEvent>>(
		[&](const MouseMoveEvent& _event) {
			if (m_WindowHnd->IsFocused()) {
				m_Player->OnMouseMove(*m_WindowHnd, _event.xPos, _event.yPos);
			}
	});

	m_WindowHnd->GetEventDispatcher().Subscribe<MouseMoveEvent>(mouseMoveHandler); 

	const auto keyPressHandler = std::make_shared<EventHandler<KeyPressEvent>>(
		[&](const KeyPressEvent& _event) {
			// store key press to buffer
			m_KeyBuffer[_event.button] = !_event.action ? false : true;
	});

	m_WindowHnd->GetEventDispatcher().Subscribe<KeyPressEvent>(keyPressHandler); 

	const auto resizeHandler = std::make_shared<EventHandler<WindowResizeEvent>>(
		[&](const WindowResizeEvent& _event) {
			// resize viewport on window resize
			m_RenderCore.SetViewport(0, 0, _event.width, _event.height);
			// regenerate projection matrix
			m_Projection = CameraUtility::CreateProjectionMatrix(FOV_Y,
				m_WindowHnd->GetAspectRatio(), Z_NEAR, Z_FAR);
	});

	m_WindowHnd->GetEventDispatcher().Subscribe<WindowResizeEvent>(resizeHandler); 

	const auto scrollHandler = std::make_shared<EventHandler<MouseScrollEvent>>(
		[&](const MouseScrollEvent& _event) {
		if (m_WindowHnd->IsFocused()) {
			m_Player->OnMouseScroll(*m_WindowHnd, 0, _event.direction);
		}
	});

	m_WindowHnd->GetEventDispatcher().Subscribe<MouseScrollEvent>(scrollHandler);

	// init projection matrix
	m_Projection = CameraUtility::CreateProjectionMatrix(FOV_Y,
		m_WindowHnd->GetAspectRatio(), Z_NEAR, Z_FAR);

	if (!SetupEngine()) {
		LOG_ERROR(LOG_HEADER << "Failed to Setup Engine")
		return false;
	}

	return true;
}

void GameEngine::StartRenderLoop() {
	glfwSwapInterval(0);
	while (!m_WindowHnd->QueryCloseRequested()) {
		// notify render core of frame
		m_RenderCore.OnFrame();
		// render frame
		OnFrame();
		// clean up
		m_WindowHnd->SwapBuffers();
		m_WindowCore.PollEvents();
		m_Player->OnFrame(m_KeyBuffer, m_FrameTime);
		m_FrameTime.OnFrame();
	}
}

void GameEngine::ShutdownEngine() const {
	LOG_INFO(LOG_HEADER + "Shutting Down Engine")
	m_RenderCore.ShutdownCore();
	m_WindowHnd->DestroyWindow(); 
	m_WindowCore.ShutdownCore();
}