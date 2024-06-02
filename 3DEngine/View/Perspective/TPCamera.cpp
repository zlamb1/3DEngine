#include "TPCamera.h"

#include "Logger.h"

void TPCamera::OnMouseMove(const WindowHnd& window, const Vec2d& position) {
	if (window.IsMouseBtnPressed(WindowHnd::LEFT)) {
		const Vec2d lastPosition = window.GetLastMousePosition(); 
		const double dx = position.x - lastPosition.x, dy = position.y - lastPosition.y;
		m_Rotation += glm::vec3(-dx, dy, 0) * m_MouseSens;
		ClampPitch();
		UpdateViewModel();
	}
}

void TPCamera::OnMouseScroll(const WindowHnd& window, const ScrollDirection& scrollDir) {
	constexpr float ZOOM_SPEED = 1.25f;
	if (scrollDir == UP) {
		m_Zoom *= ZOOM_SPEED;
	} else {
		m_Zoom /= ZOOM_SPEED;
	}
}

void TPCamera::UpdateViewModel() {
	m_ViewMatrix = glm::lookAt(CameraUtility::VectorInUnitSphere(m_Position, m_Rotation.x, m_Rotation.y) * m_Zoom,
		m_Position, CameraUtility::UP_VECTOR);
	// compute proj
	m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix; 
}
